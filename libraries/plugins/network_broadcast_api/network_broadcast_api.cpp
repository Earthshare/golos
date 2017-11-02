#include <steemit/plugins/network_broadcast_api/network_broadcast_api.hpp>
#include <steemit/plugins/network_broadcast_api/network_broadcast_api_plugin.hpp>
#include <steemit/plugins/json_rpc/utility.hpp>

#include <appbase/application.hpp>

#include <boost/thread/future.hpp>
#include <boost/thread/lock_guard.hpp>

namespace steemit { namespace plugins { namespace network_broadcast_api {


            using std::vector;
            using fc::variant;
            using fc::optional;
            using steemit::protocol::signed_transaction;


            struct broadcast_transaction_t {
                signed_transaction   trx;
                int32_t              max_block_age = -1;
            };

            struct broadcast_block_t {
                signed_block   block;
            };

            using confirmation_callback = std::function< void( const broadcast_transaction_synchronous_return& ) > ;

            struct network_broadcast_api::impl final {
            public:
                impl():_p2p( appbase::app().get_plugin< p2p::p2p_plugin >() ),
                       _chain( appbase::app().get_plugin< chain_interface::chain_plugin >() ) {}

                p2p::p2p_plugin&                                      _p2p;
                chain_interface::chain_plugin&                        _chain;
                map< transaction_id_type, confirmation_callback >     _callbacks;
                map< time_point_sec, vector< transaction_id_type > >  _callback_expirations;
                boost::mutex                                          _mtx;
            };

            network_broadcast_api::network_broadcast_api(){
               JSON_RPC_REGISTER_API( STEEM_NETWORK_BROADCAST_API_PLUGIN_NAME );
            }

            network_broadcast_api::~network_broadcast_api() {}

            DEFINE_API( network_broadcast_api, broadcast_transaction ) {
                auto tmp = args.args->at(0).as<broadcast_transaction_t>();
                FC_ASSERT( !check_max_block_age( tmp.max_block_age ) );
                pimpl->_chain.db().push_transaction( tmp.trx );
                pimpl->_p2p.broadcast_transaction( tmp.trx );

                return broadcast_transaction_return();
        }

        DEFINE_API( network_broadcast_api, broadcast_transaction_synchronous ) {
        auto tmp = args.args->at(0).as<broadcast_transaction_t>();
        FC_ASSERT( !check_max_block_age( tmp.max_block_age ) );
            boost::promise< broadcast_transaction_synchronous_return > p;
            {
                boost::lock_guard< boost::mutex > guard( pimpl->_mtx );
                pimpl->_callbacks[ tmp.trx.id() ] = [&p]( const broadcast_transaction_synchronous_return& r ) {
                    p.set_value( r );
                };
                pimpl->_callback_expirations[ tmp.trx.expiration ].push_back( tmp.trx.id() );
            }

            pimpl->_chain.db().push_transaction( tmp.trx );
            pimpl->_p2p.broadcast_transaction( tmp.trx );

            return p.get_future().get();
        }

DEFINE_API( network_broadcast_api, broadcast_block ) {
    auto tmp = args.args->at(0).as<broadcast_block_t>();
    pimpl->_chain.db().push_block( tmp.block );
    pimpl->_p2p.broadcast_block( tmp.block );
return broadcast_block_return();
}

bool network_broadcast_api::check_max_block_age( int32_t max_block_age ) const {
   return pimpl->_chain.db().with_read_lock(
           [&]() {
               if( max_block_age < 0 )
                   return false;

               fc::time_point_sec now = fc::time_point::now();
               const auto& dgpo = pimpl->_chain.db().get_dynamic_global_properties();

               return ( dgpo.time < now - fc::seconds( max_block_age ) );
           }
   );
}

void network_broadcast_api::on_applied_block( const signed_block& b ) {
   int32_t block_num = int32_t(b.block_num());
   if( pimpl->_callbacks.size() ) {
      for( size_t trx_num = 0; trx_num < b.transactions.size(); ++trx_num ) {
         const auto& trx = b.transactions[trx_num];
         auto id = trx.id();
         auto itr = pimpl->_callbacks.find( id );
         if( itr == pimpl->_callbacks.end() ) continue;
         confirmation_callback callback = itr->second;
          pimpl->_callbacks.erase( itr );
         callback( broadcast_transaction_synchronous_return( id, block_num, int32_t( trx_num ), false ) );
      }
   }

   /// clear all expirations
   while( true ) {
      auto exp_it = pimpl->_callback_expirations.begin();
      if( exp_it == pimpl->_callback_expirations.end() )
         break;
      if( exp_it->first >= b.timestamp )
         break;
      for( const transaction_id_type& txid : exp_it->second ) {
         auto cb_it = pimpl->_callbacks.find( txid );
         // If it's empty, that means the transaction has been confirmed and has been deleted by the above check.
         if( cb_it == pimpl->_callbacks.end() )
            continue;

         confirmation_callback callback = cb_it->second;
         transaction_id_type txid_byval = txid;    // can't pass in by reference as it's going to be deleted
         callback( broadcast_transaction_synchronous_return( txid_byval, block_num, -1, true ) );

          pimpl->_callbacks.erase( cb_it );
      }
       pimpl->_callback_expirations.erase( exp_it );
   }
}

} } } // steem::plugins::network_broadcast_api


FC_REFLECT( (steemit::plugins::network_broadcast_api::broadcast_transaction_t),
            (trx)(max_block_age) )

FC_REFLECT( (steemit::plugins::network_broadcast_api::broadcast_block_t),
            (block) )