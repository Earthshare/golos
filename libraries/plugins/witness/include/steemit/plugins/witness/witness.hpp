#pragma once


#include <steemit/chain/database.hpp>
#include <boost/program_options/variables_map.hpp>
#include <appbase/application.hpp>
#include <steemit/plugins/chain/chain_plugin.hpp>
#include <plugins/p2p/include/steemit/plugins/p2p/p2p_plugin.hpp>

namespace steemit {
    namespace plugins {
        namespace witness_plugin {

            using std::string;
            using protocol::public_key_type;
            using steemit::protocol::block_id_type;

            namespace block_production_condition {
                enum block_production_condition_enum {
                    produced = 0,
                    not_synced = 1,
                    not_my_turn = 2,
                    not_time_yet = 3,
                    no_private_key = 4,
                    low_participation = 5,
                    lag = 6,
                    consecutive = 7,
                    wait_for_genesis = 8,
                    exception_producing_block = 9
                };
            }

            class witness_plugin final : public appbase::plugin<witness_plugin> {
            public:
                APPBASE_PLUGIN_REQUIRES((chain_interface::chain_plugin) (p2p::p2p_plugin))
                constexpr static const char* __name__ ="witness";
                static const std::string& name() { static std::string name = __name__; return name; }

                witness_plugin();

                ~witness_plugin();



                void set_program_options(
                        boost::program_options::options_description &command_line_options,
                        boost::program_options::options_description &config_file_options
                )override;

                void set_block_production(bool allow);

                void plugin_initialize(const boost::program_options::variables_map &options)override;

                void plugin_startup()override;

                void plugin_shutdown()override;

            private:
                void on_applied_block(const chain::signed_block &b);

                void start_mining(const fc::ecc::public_key &pub, const fc::ecc::private_key &pk,
                                  const string &name, const steemit::chain::signed_block &b);


                void schedule_production_loop();

                block_production_condition::block_production_condition_enum block_production_loop();

                block_production_condition::block_production_condition_enum
                maybe_produce_block(fc::mutable_variant_object &capture);

                boost::program_options::variables_map _options;
                bool _production_enabled = false;
                uint32_t _required_witness_participation = 33 * STEEMIT_1_PERCENT;
                uint32_t _production_skip_flags = steemit::chain::database::skip_nothing;
                uint32_t _mining_threads = 0;

                uint64_t _head_block_num = 0;
                block_id_type _head_block_id = block_id_type();
                uint64_t _total_hashes = 0;
                fc::time_point _hash_start_time;

                std::vector<std::shared_ptr<fc::thread>> _thread_pool;

                std::map<public_key_type, fc::ecc::private_key> _private_keys;
                std::set<string> _witnesses;
                std::map<string, public_key_type> _miners;
                protocol::chain_properties<0, 17, 0> _miner_prop_vote;
                fc::future<void> _block_production_task;
            };

        }
    }
} //steemit::witness_plugin