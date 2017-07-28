#pragma once

#include <steemit/protocol/exceptions.hpp>

#define STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(op_name)                \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      op_name ## _validate_exception,                                 \
      steemit::chain::operation_validate_exception,                  \
      4040000 + 100 * protocol::operation::tag< protocol::op_name ## _operation >::value, \
      #op_name "_operation validation exception"                      \
      )                                                               \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      op_name ## _evaluate_exception,                                 \
      steemit::chain::operation_evaluate_exception,                  \
      4050000 + 100 * protocol::operation::tag< protocol::op_name ## _operation >::value, \
      #op_name "_operation evaluation exception"                      \
      )

#define STEEMIT_DECLARE_OP_VALIDATE_EXCEPTION(exc_name, op_name, seqnum, msg) \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      op_name ## _ ## exc_name,                                       \
      steemit::chain::op_name ## _validate_exception,                \
      4040000 + 100 * protocol::operation::tag< protocol::op_name ## _operation >::value  \
         + seqnum,                                                    \
      msg                                                             \
      )

#define STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(exc_name, op_name, seqnum, msg) \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      op_name ## _ ## exc_name,                                       \
      steemit::chain::op_name ## _evaluate_exception,                \
      4050000 + 100 * protocol::operation::tag< protocol::op_name ## _operation >::value  \
         + seqnum,                                                    \
      msg                                                             \
      )

#define STEEMIT_DECLARE_INTERNAL_EXCEPTION(exc_name, seqnum, msg)  \
   FC_DECLARE_DERIVED_EXCEPTION(                                      \
      internal_ ## exc_name,                                          \
      steemit::chain::internal_exception,                            \
      4990000 + seqnum,                                               \
      msg                                                             \
      )

#define STEEMIT_TRY_NOTIFY(signal, ...)                                     \
   try                                                                        \
   {                                                                          \
      signal( __VA_ARGS__ );                                                  \
   }                                                                          \
   catch( const steemit::chain::plugin_exception& e )                         \
   {                                                                          \
      elog( "Caught plugin exception: ${e}", ("e", e.to_detail_string() ) );  \
      throw;                                                                  \
   }                                                                          \
   catch( const fc::exception& e )                                            \
   {                                                                          \
      elog( "Caught exception in plugin: ${e}", ("e", e.to_detail_string() ) ); \
   }                                                                          \
   catch( ... )                                                               \
   {                                                                          \
      wlog( "Caught unexpected exception in plugin" );                        \
   }

namespace steemit {
    namespace chain {

        FC_DECLARE_EXCEPTION(chain_exception, 4000000, "blockchain exception")

        FC_DECLARE_DERIVED_EXCEPTION(database_query_exception, steemit::chain::chain_exception, 4010000, "database query exception")

        FC_DECLARE_DERIVED_EXCEPTION(block_validate_exception, steemit::chain::chain_exception, 4020000, "block validation exception")

        FC_DECLARE_DERIVED_EXCEPTION(transaction_exception, steemit::chain::chain_exception, 4030000, "transaction validation exception")

        FC_DECLARE_DERIVED_EXCEPTION(operation_validate_exception, steemit::chain::chain_exception, 4040000, "operation validation exception")

        FC_DECLARE_DERIVED_EXCEPTION(operation_evaluate_exception, steemit::chain::chain_exception, 4050000, "operation evaluation exception")

        FC_DECLARE_DERIVED_EXCEPTION(utility_exception, steemit::chain::chain_exception, 4060000, "utility method exception")

        FC_DECLARE_DERIVED_EXCEPTION(invalid_pts_address, steemit::chain::utility_exception, 3060001, "invalid pts address")

        FC_DECLARE_DERIVED_EXCEPTION(undo_database_exception, steemit::chain::chain_exception, 4070000, "undo database exception")

        FC_DECLARE_DERIVED_EXCEPTION(unlinkable_block_exception, steemit::chain::chain_exception, 4080000, "unlinkable block")

        FC_DECLARE_DERIVED_EXCEPTION(unknown_hardfork_exception, steemit::chain::chain_exception, 4090000, "chain attempted to apply unknown hardfork")

        FC_DECLARE_DERIVED_EXCEPTION(plugin_exception, steemit::chain::chain_exception, 4100000, "plugin exception")

        FC_DECLARE_DERIVED_EXCEPTION(block_log_exception, steemit::chain::chain_exception, 4110000, "block log exception")

        FC_DECLARE_DERIVED_EXCEPTION(pop_empty_chain, steemit::chain::undo_database_exception, 4070001, "there are no blocks to pop")

        FC_DECLARE_DERIVED_EXCEPTION(insufficient_feeds, steemit::chain::chain_exception, 37006, "insufficient feeds")

        FC_DECLARE_DERIVED_EXCEPTION(black_swan_exception, steemit::chain::chain_exception, 3090000, "black swan")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(transfer);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(from_account_not_whitelisted, transfer, 1, "owner mismatch")

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(to_account_not_whitelisted, transfer, 2, "owner mismatch")

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(restricted_transfer_asset, transfer, 3, "restricted transfer asset")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(account_create);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(max_auth_exceeded, account_create, 1, "Exceeds max authority fan-out")

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(auth_account_not_found, account_create, 2, "Auth account not found")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(account_update);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(max_auth_exceeded, account_update, 1, "Exceeds max authority fan-out")

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(auth_account_not_found, account_update, 2, "Auth account not found")

        FC_DECLARE_DERIVED_EXCEPTION(internal_exception, steemit::chain::chain_exception, 4990000, "internal exception")

        STEEMIT_DECLARE_INTERNAL_EXCEPTION(verify_auth_max_auth_exceeded, 1, "Exceeds max authority fan-out")

        STEEMIT_DECLARE_INTERNAL_EXCEPTION(verify_auth_account_not_found, 2, "Auth account not found")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(proposal_create);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(review_period_required, proposal_create, 1, "review_period required")

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(review_period_insufficient, proposal_create, 2, "review_period insufficient")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(asset_reserve);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(invalid_on_mia, asset_reserve, 1, "invalid on mia")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(call_order_update);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(unfilled_margin_call, call_order_update, 1, "Updating call order would trigger a margin call that cannot be fully filled")

        STEEMIT_DECLARE_OP_BASE_EXCEPTIONS(override_transfer);

        STEEMIT_DECLARE_OP_EVALUATE_EXCEPTION(not_permitted, override_transfer, 1, "not permitted")
    }
} // steemit::chain
