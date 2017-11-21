#pragma once

#include <functional>
#include <map>
#include <memory>
#include <vector>

#include <fc/optional.hpp>
#include <fc/variant_object.hpp>
#include <golos/plugins/json_rpc/utility.hpp>
#include <golos/plugins/json_rpc/plugin.hpp>
#include <golos/plugins/database_api/applied_operation.hpp>
#include <golos/plugins/database_api/state.hpp>
#include <golos/plugins/database_api/discussion_query.hpp>
#include <golos/plugins/database_api/api_objects/feed_history_api_object.hpp>
#include <golos/plugins/database_api/api_objects/owner_authority_history_api_object.hpp>
#include <golos/plugins/database_api/api_objects/account_recovery_request_api_object.hpp>
#include <golos/plugins/database_api/api_objects/savings_withdraw_api_object.hpp>

#include "forward.hpp"

namespace golos {
    namespace plugins {
        namespace database_api {
            using namespace golos::chain;
            using namespace golos::protocol;
            using fc::variant;
            using std::vector;
            using plugins::json_rpc::void_type;
            using plugins::json_rpc::msg_pack;

            struct scheduled_hardfork {
                hardfork_version hf_version;
                fc::time_point_sec live_time;
            };

            struct withdraw_route {
                std::string from_account;
                std::string to_account;
                uint16_t percent;
                bool auto_vest;
            };

            enum withdraw_route_type {
                incoming, outgoing, all
            };


            struct tag_count_object {
                string tag;
                uint32_t count;
            };

            struct get_tags_used_by_author {
                vector<tag_count_object> tags;
            };

            struct signed_block_api_object : public signed_block {
                signed_block_api_object(const signed_block &block) : signed_block(block) {
                    block_id = id();
                    signing_key = signee();
                    transaction_ids.reserve(transactions.size());
                    for (const signed_transaction &tx : transactions) {
                        transaction_ids.push_back(tx.id());
                    }
                }

                signed_block_api_object() {
                }

                block_id_type block_id;
                public_key_type signing_key;
                vector<transaction_id_type> transaction_ids;
            };


            ///account_history_api
            struct operation_api_object {
                operation_api_object() {
                }

                operation_api_object(const golos::chain::operation_object &op_obj) : trx_id(op_obj.trx_id),
                        block(op_obj.block), trx_in_block(op_obj.trx_in_block), virtual_op(op_obj.virtual_op),
                        timestamp(op_obj.timestamp) {
                    op = fc::raw::unpack<golos::protocol::operation>(op_obj.serialized_op);
                }

                golos::protocol::transaction_id_type trx_id;
                uint32_t block = 0;
                uint32_t trx_in_block = 0;
                uint16_t op_in_trx = 0;
                uint64_t virtual_op = 0;
                fc::time_point_sec timestamp;
                golos::protocol::operation op;
            };


            using get_account_history_return_type = map<uint32_t, applied_operation>;
            using get_tags_used_by_author_return_type=vector<pair<std::string, uint32_t>>;
            using chain_properties_17 = chain_properties<0, 17, 0>;
            using price_17 = price<0, 17, 0>;
            using asset_17 = asset<0, 17, 0>;


            ///               API,                                    args,                return
            DEFINE_API_ARGS(get_trending_tags, msg_pack, vector<tag_api_object>)
            DEFINE_API_ARGS(get_active_witnesses, msg_pack, vector<account_name_type>)
            DEFINE_API_ARGS(get_block_header, msg_pack, optional<block_header>)
            DEFINE_API_ARGS(get_block, msg_pack, optional<block_header>)
            DEFINE_API_ARGS(get_ops_in_block, msg_pack, vector<applied_operation>)
            DEFINE_API_ARGS(get_config, msg_pack, variant_object)
            DEFINE_API_ARGS(get_dynamic_global_properties, msg_pack, dynamic_global_property_api_object)
            DEFINE_API_ARGS(get_chain_properties, msg_pack, chain_properties_17)
            DEFINE_API_ARGS(get_current_median_history_price, msg_pack, price_17)
            DEFINE_API_ARGS(get_feed_history, msg_pack, feed_history_api_object)
            DEFINE_API_ARGS(get_witness_schedule, msg_pack, witness_schedule_api_object)
            DEFINE_API_ARGS(get_hardfork_version, msg_pack, hardfork_version)
            DEFINE_API_ARGS(get_next_scheduled_hardfork, msg_pack, scheduled_hardfork)
            DEFINE_API_ARGS(get_reward_fund, msg_pack, reward_fund_api_object)
            DEFINE_API_ARGS(get_key_references, msg_pack, vector<vector<account_name_type> >)
            DEFINE_API_ARGS(get_accounts, msg_pack, vector<extended_account>)
            DEFINE_API_ARGS(lookup_account_names, msg_pack, vector<optional<account_api_object> >)
            DEFINE_API_ARGS(lookup_accounts, msg_pack, set<string>)
            DEFINE_API_ARGS(get_account_count, msg_pack, uint64_t)
            DEFINE_API_ARGS(get_owner_history, msg_pack, vector<owner_authority_history_api_object>)
            DEFINE_API_ARGS(get_recovery_request, msg_pack, optional<account_recovery_request_api_object>)
            DEFINE_API_ARGS(get_escrow, msg_pack, optional<escrow_api_object>)
            DEFINE_API_ARGS(get_withdraw_routes, msg_pack, vector<withdraw_route>)
            DEFINE_API_ARGS(get_account_bandwidth, msg_pack, optional<account_bandwidth_api_object>)
            DEFINE_API_ARGS(get_savings_withdraw_from, msg_pack, vector<savings_withdraw_api_object>)
            DEFINE_API_ARGS(get_savings_withdraw_to, msg_pack, vector<savings_withdraw_api_object>)
            DEFINE_API_ARGS(get_vesting_delegations, msg_pack, vector<vesting_delegation_api_object>)
            DEFINE_API_ARGS(get_expiring_vesting_delegations, msg_pack,
                            vector<vesting_delegation_expiration_api_object>)
            DEFINE_API_ARGS(get_witnesses, msg_pack, vector<optional<witness_api_object> >)
            DEFINE_API_ARGS(get_conversion_requests, msg_pack, vector<convert_request_api_object>)
            DEFINE_API_ARGS(get_witness_by_account, msg_pack, optional<witness_api_object>)
            DEFINE_API_ARGS(get_witnesses_by_vote, msg_pack, vector<witness_api_object>)
            DEFINE_API_ARGS(lookup_witness_accounts, msg_pack, set<account_name_type>)
            DEFINE_API_ARGS(get_open_orders, msg_pack, vector<extended_limit_order>)
            DEFINE_API_ARGS(get_witness_count, msg_pack, uint64_t)
            DEFINE_API_ARGS(get_transaction_hex, msg_pack, string)
            DEFINE_API_ARGS(get_transaction, msg_pack, annotated_signed_transaction)
            DEFINE_API_ARGS(get_required_signatures, msg_pack, set<public_key_type>)
            DEFINE_API_ARGS(get_potential_signatures, msg_pack, set<public_key_type>)
            DEFINE_API_ARGS(verify_authority, msg_pack, bool)
            DEFINE_API_ARGS(verify_account_authority, msg_pack, bool)
            DEFINE_API_ARGS(get_active_votes, msg_pack, vector<vote_state>)
            DEFINE_API_ARGS(get_account_votes, msg_pack, vector<account_vote>)
            DEFINE_API_ARGS(get_content, msg_pack, discussion)
            DEFINE_API_ARGS(get_content_replies, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_tags_used_by_author, msg_pack, get_tags_used_by_author_return_type)
            DEFINE_API_ARGS(get_discussions_by_payout, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_post_discussions_by_payout, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_comment_discussions_by_payout, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_trending, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_created, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_active, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_cashout, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_votes, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_children, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_hot, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_feed, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_blog, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_comments, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_promoted, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_replies_by_last_update, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_discussions_by_author_before_date, msg_pack, vector<discussion>)
            DEFINE_API_ARGS(get_account_history, msg_pack, get_account_history_return_type)
            ///asset
            DEFINE_API_ARGS(get_assets_dynamic_data, msg_pack, vector<optional<asset_dynamic_data_object>>)
            DEFINE_API_ARGS(get_assets_by_issuer, msg_pack, vector<optional<asset_object>>)
            ///categories
            DEFINE_API_ARGS(get_trending_categories, msg_pack, vector<category_api_object>)
            ///
            DEFINE_API_ARGS(get_account_balances, msg_pack, vector<asset_17>)
            DEFINE_API_ARGS(get_active_categories, msg_pack, vector<category_api_object>)
            DEFINE_API_ARGS(get_recent_categories, msg_pack, vector<category_api_object>)
            DEFINE_API_ARGS(get_proposed_transactions, msg_pack, vector<proposal_object>)
            DEFINE_API_ARGS(list_assets, msg_pack, vector<asset_object>)
            DEFINE_API_ARGS(get_bitassets_data, msg_pack, vector<optional<asset_bitasset_data_object>>)
            DEFINE_API_ARGS(get_miner_queue, msg_pack, vector<account_name_type>)
            DEFINE_API_ARGS(get_assets, msg_pack, vector<optional<asset_object>>)
            DEFINE_API_ARGS(get_best_categories, msg_pack, vector<category_api_object>)
            DEFINE_API_ARGS(lookup_asset_symbols, msg_pack, vector<optional<asset_object>>)
            DEFINE_API_ARGS(get_payout_extension_cost, msg_pack, asset_17)
            DEFINE_API_ARGS(get_payout_extension_time, msg_pack, fc::time_point_sec)


            /**
             * @brief The database_api class implements the RPC API for the chain database.
             *
             * This API exposes accessors on the database which query state tracked by a blockchain validating node. This API is
             * read-only; all modifications to the database must be performed via transactions. Transactions are broadcast via
             * the @ref network_broadcast_api.
             */
            class plugin final : public appbase::plugin<plugin> {
            public:
                constexpr static const char *plugin_name = "database_api";

                static const std::string &name() {
                    static std::string name = plugin_name;
                    return name;
                }

                APPBASE_PLUGIN_REQUIRES(
                        (json_rpc::plugin)
                        (chain::plugin)
                )

                void set_program_options(boost::program_options::options_description &cli, boost::program_options::options_description &cfg) override{}

                void plugin_initialize(const boost::program_options::variables_map &options) override;

                void plugin_startup() override{}

                void plugin_shutdown() override{}

                plugin();

                ~plugin();

                ///////////////////
                // Subscriptions //
                ///////////////////

                void set_subscribe_callback(std::function<void(const variant &)> cb, bool clear_filter);

                void set_pending_transaction_callback(std::function<void(const variant &)> cb);

                void set_block_applied_callback(std::function<void(const variant &block_header)> cb);

                /**
                 * @brief Stop receiving any notifications
                 *
                 * This unsubscribes from all subscribed markets and objects.
                 */
                void cancel_all_subscriptions();

                DECLARE_API((get_trending_tags)

                                    /**
                                     *  This API is a short-cut for returning all of the state required for a particular URL
                                     *  with a single query.
                                     */

                                    (get_trending_categories)

                                    (get_best_categories)

                                    (get_active_categories)

                                    (get_recent_categories)

                                    (get_active_witnesses)

                                    (get_miner_queue)

                                    /////////////////////////////
                                    // Blocks and transactions //
                                    /////////////////////////////

                                    /**
                                     * @brief Retrieve a block header
                                     * @param block_num Height of the block whose header should be returned
                                     * @return header of the referenced block, or null if no matching block was found
                                     */

                                    (get_block_header)

                                    /**
                                     * @brief Retrieve a full, signed block
                                     * @param block_num Height of the block to be returned
                                     * @return the referenced block, or null if no matching block was found
                                     */
                                    (get_block)

                                    /**
                                     *  @brief Get sequence of operations included/generated within a particular block
                                     *  @param block_num Height of the block whose generated virtual operations should be returned
                                     *  @param only_virtual Whether to only include virtual operations in returned results (default: true)
                                     *  @return sequence of operations included/generated within the block
                                     */
                                    (get_ops_in_block)

                                    /////////////
                                    // Globals //
                                    /////////////

                                    /**
                                     * @brief Retrieve compile-time constants
                                     */
                                    (get_config)

                                    /**
                                     * @brief Retrieve the current @ref dynamic_global_property_object
                                     */
                                    (get_dynamic_global_properties)

                                    (get_chain_properties)

                                    (get_current_median_history_price)

                                    (get_feed_history)

                                    (get_witness_schedule)

                                    (get_hardfork_version)

                                    (get_next_scheduled_hardfork)

                                    (get_reward_fund)

                                    //////////////
                                    // Accounts //
                                    //////////////

                                    (get_accounts)

                                    /**
                                     * @brief Get a list of accounts by name
                                     * @param account_names Names of the accounts to retrieve
                                     * @return The accounts holding the provided names
                                     *
                                     * This function has semantics identical to @ref get_objects
                                     */
                                    (lookup_account_names)

                                    /**
                                     * @brief Get names and IDs for registered accounts
                                     * @param lower_bound_name Lower bound of the first name to return
                                     * @param limit Maximum number of results to return -- must not exceed 1000
                                     * @return Map of account names to corresponding IDs
                                     */
                                    (lookup_accounts)

                                    //////////////
                                    // Balances //
                                    //////////////

                                    /**
                                     * @brief Get an account's balances in various assets
                                     * @param name of the account to get balances for
                                     * @param assets names of the assets to get balances of; if empty, get all assets account has a balance in
                                     * @return Balances of the account
                                     */
                                    (get_account_balances)

                                    /**
                                     * @brief Get the total number of accounts registered with the blockchain
                                     */
                                    (get_account_count)

                                    (get_owner_history)

                                    (get_recovery_request)

                                    (get_escrow)

                                    (get_withdraw_routes)

                                    (get_account_bandwidth)

                                    (get_savings_withdraw_from)

                                    (get_savings_withdraw_to)

                                    (get_vesting_delegations)

                                    (get_expiring_vesting_delegations)

                                    ///////////////
                                    // Witnesses //
                                    ///////////////

                                    /**
                                     * @brief Get a list of witnesses by ID
                                     * @param witness_ids IDs of the witnesses to retrieve
                                     * @return The witnesses corresponding to the provided IDs
                                     *
                                     * This function has semantics identical to @ref get_objects
                                     */
                                    (get_witnesses)

                                    (get_conversion_requests)

                                    /**
                                     * @brief Get the witness owned by a given account
                                     * @param account The name of the account whose witness should be retrieved
                                     * @return The witness object, or null if the account does not have a witness
                                     */
                                    (get_witness_by_account)

                                    /**
                                     *  This method is used to fetch witnesses with pagination.
                                     *
                                     *  @return an array of `count` witnesses sorted by total votes after witness `from` with at most `limit' results.
                                     */
                                    (get_witnesses_by_vote)

                                    /**
                                     * @brief Get names and IDs for registered witnesses
                                     * @param lower_bound_name Lower bound of the first name to return
                                     * @param limit Maximum number of results to return -- must not exceed 1000
                                     * @return Map of witness names to corresponding IDs
                                     */
                                    (lookup_witness_accounts)

                                    /**
                                     * @brief Get the total number of witnesses registered with the blockchain
                                     */
                                    (get_witness_count)

                                    ////////////
                                    // Assets //
                                    ////////////

                                    /**
                                     * @brief Get a list of assets by ID
                                     * @param asset_symbols IDs of the assets to retrieve
                                     * @return The assets corresponding to the provided IDs
                                     *
                                     * This function has semantics identical to @ref get_objects
                                     */
                                    (get_assets)

                                    (get_assets_by_issuer)

                                    (get_assets_dynamic_data)

                                    (get_bitassets_data)

                                    /**
                                     * @brief Get assets alphabetically by symbol name
                                     * @param lower_bound_symbol Lower bound of symbol names to retrieve
                                     * @param limit Maximum number of assets to fetch (must not exceed 100)
                                     * @return The assets found
                                     */
                                    (list_assets)

                                    /**
                                     * @brief Get a list of assets by symbol
                                     * @param asset_symbols Symbols or stringified IDs of the assets to retrieve
                                     * @return The assets corresponding to the provided symbols or IDs
                                     *
                                     * This function has semantics identical to @ref get_objects
                                     */
                                    (lookup_asset_symbols)

                                    ////////////////////////////
                                    // Authority / Validation //
                                    ////////////////////////////

                                    /// @brief Get a hexdump of the serialized binary form of a transaction
                                    (get_transaction_hex)

                                    (get_transaction)

                                    /**
                                     *  This API will take a partially signed transaction and a set of public keys that the owner has the ability to sign for
                                     *  and return the minimal subset of public keys that should add signatures to the transaction.
                                     */
                                    (get_required_signatures)

                                    /**
                                     *  This method will return the set of all public keys that could possibly sign for a given transaction.  This call can
                                     *  be used by wallets to filter their set of public keys to just the relevant subset prior to calling @ref get_required_signatures
                                     *  to get the minimum subset.
                                     */
                                    (get_potential_signatures)

                                    /**
                                     * @return true of the @ref trx has all of the required signatures, otherwise throws an exception
                                     */
                                    (verify_authority)

                                    /*
                                     * @return true if the signers have enough authority to authorize an account
                                     */
                                    (verify_account_authority)

                                    /**
                                     *  if permlink is "" then it will return all votes for author
                                     */
                                    (get_active_votes)

                                    (get_account_votes)


                                    (get_content)

                                    (get_content_replies)

                                    /**
                                     * Used to retrieve top 1000 tags list used by an author sorted by most frequently used
                                     * @param author select tags of this author
                                     * @return vector of top 1000 tags used by an author sorted by most frequently used
                                     **/
                                    (get_tags_used_by_author)

                                    /**
                                     * Used to retrieve the list of first payout discussions sorted by rshares^2 amount
                                     * @param query @ref discussion_query
                                     * @return vector of first payout mode discussions sorted by rshares^2 amount
                                     **/
                                    (get_discussions_by_trending)

                                    /**
                                     * Used to retrieve the list of discussions sorted by created time
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by created time
                                     **/
                                    (get_discussions_by_created)

                                    /**
                                     * Used to retrieve the list of discussions sorted by last activity time
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by last activity time
                                     **/
                                    (get_discussions_by_active)

                                    /**
                                     * Used to retrieve the list of discussions sorted by cashout time
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by last cashout time
                                     **/
                                    (get_discussions_by_cashout)

                                    /**
                                     * Used to retrieve the list of discussions sorted by net rshares amount
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by net rshares amount
                                     **/
                                    (get_discussions_by_payout)

                                    (get_post_discussions_by_payout)

                                    (get_comment_discussions_by_payout)

                                    /**
                                     * Used to retrieve the list of discussions sorted by direct votes amount
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by direct votes amount
                                     **/
                                    (get_discussions_by_votes)

                                    /**
                                     * Used to retrieve the list of discussions sorted by children posts amount
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by children posts amount
                                     **/
                                    (get_discussions_by_children)

                                    /**
                                     * Used to retrieve the list of discussions sorted by hot amount
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by hot amount
                                     **/
                                    (get_discussions_by_hot)

                                    /**
                                     * Used to retrieve the list of discussions from the feed of a specific author
                                     * @param query @ref discussion_query
                                     * @attention @ref discussion_query#select_authors must be set and must contain the @ref discussion_query#start_author param if the last one is not null
                                     * @return vector of discussions from the feed of authors in @ref discussion_query#select_authors
                                     **/
                                    (get_discussions_by_feed)

                                    /**
                                     * Used to retrieve the list of discussions from the blog of a specific author
                                     * @param query @ref discussion_query
                                     * @attention @ref discussion_query#select_authors must be set and must contain the @ref discussion_query#start_author param if the last one is not null
                                     * @return vector of discussions from the blog of authors in @ref discussion_query#select_authors
                                     **/
                                    (get_discussions_by_blog)

                                    (get_discussions_by_comments)

                                    /**
                                     * Used to retrieve the list of discussions sorted by promoted balance amount
                                     * @param query @ref discussion_query
                                     * @return vector of discussions sorted by promoted balance amount
                                     **/
                                    (get_discussions_by_promoted)


                                    /**
                                     *  Return the active discussions with the highest cumulative pending payouts without respect to category, total
                                     *  pending payout means the pending payout of all children as well.
                                     */
                                    (get_replies_by_last_update)


                                    /**
                                     *  This method is used to fetch all posts/comments by start_author that occur after before_date and start_permlink with up to limit being returned.
                                     *
                                     *  If start_permlink is empty then only before_date will be considered. If both are specified the eariler to the two metrics will be used. This
                                     *  should allow easy pagination.
                                     */
                                    (get_discussions_by_author_before_date)

                                    /**
                                     *  Account operations have sequence numbers from 0 to N where N is the most recent operation. This method
                                     *  returns operations in the range [from-limit, from]
                                     *
                                     *  @param from - the absolute sequence number, -1 means most recent, limit is the number of operations before from.
                                     *  @param limit - the maximum number of items that can be queried (0 to 1000], must be less than from
                                     */
                                    (get_account_history)

                                    /**
                                     * Used to retrieve comment payout window extension cost by time
                                     * @param author comment author
                                     * @param permlink comment permlink
                                     * @param time deadline time the payout window pretends to be extended for
                                     * @return SBD amount required to set payout window duration up to time passed
                                     */

                                    (get_payout_extension_cost)

                                    /**
                                     * Used o retrieve comment payout window extension time by cost
                                     * @param author comment author
                                     * @param permlink comment permlink
                                     * @param cost SBD amount pretended to be spent on extension
                                     * @return deadline time the payout window pretends to be extended for
                                     */

                                    (get_payout_extension_time)

                                    ///////////////////////////
                                    // Proposed transactions //
                                    ///////////////////////////

                                    /**
                                     *  @return the set of proposed transactions relevant to the specified account id.
                                     */
                                    (get_proposed_transactions)

                )

            private:

                template<typename DatabaseIndex, typename DiscussionIndex>
                std::vector<discussion> feed(
                        const std::set<string> &select_set, const discussion_query &query,
                                             const std::string &start_author, const std::string &start_permlink) const;

                template<typename DatabaseIndex, typename DiscussionIndex>
                std::vector<discussion> blog(
                        const std::set<string> &select_set,
                        const discussion_query &query,
                        const std::string &start_author,
                        const std::string &start_permlink
                ) const;


                struct api_impl;
                std::shared_ptr<api_impl> my;
            };


            inline void register_database_api(){
                appbase::app().register_plugin<plugin>();
            }
        }
    }
}







FC_REFLECT((golos::plugins::database_api::scheduled_hardfork), (hf_version)(live_time));
FC_REFLECT((golos::plugins::database_api::withdraw_route), (from_account)(to_account)(percent)(auto_vest));

FC_REFLECT_ENUM(golos::plugins::database_api::withdraw_route_type, (incoming)(outgoing)(all))

FC_REFLECT((golos::plugins::database_api::tag_count_object), (tag)(count))

FC_REFLECT((golos::plugins::database_api::get_tags_used_by_author), (tags))

FC_REFLECT((golos::plugins::database_api::signed_block_api_object), (block_id)(signing_key)(transaction_ids))

FC_REFLECT((golos::plugins::database_api::operation_api_object),
           (trx_id)(block)(trx_in_block)(op_in_trx)(virtual_op)(timestamp)(op))