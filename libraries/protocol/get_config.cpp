#include <steemit/protocol/get_config.hpp>
#include <steemit/protocol/config.hpp>
#include <steemit/protocol/asset.hpp>

#include <steemit/version/version.hpp>

namespace steemit {
    namespace protocol {

        fc::variant_object get_config() {
            fc::mutable_variant_object result;

#ifdef STEEMIT_BUILD_TESTNET
            result[ "STEEMIT_BUILD_TESTNET" ] = true;
#else
            result["STEEMIT_BUILD_TESTNET"] = false;
#endif

            result["GRAPHENE_CURRENT_DB_VERSION"] = GRAPHENE_CURRENT_DB_VERSION;
            result["SBD_SYMBOL_NAME"] = SBD_SYMBOL_NAME;
            result["STEEMIT_100_PERCENT"] = STEEMIT_100_PERCENT;
            result["STEEMIT_1_PERCENT"] = STEEMIT_1_PERCENT;
            result["STEEMIT_ADDRESS_PREFIX"] = STEEMIT_ADDRESS_PREFIX;
            result["STEEMIT_APR_PERCENT_MULTIPLY_PER_BLOCK"] = STEEMIT_APR_PERCENT_MULTIPLY_PER_BLOCK;
            result["STEEMIT_APR_PERCENT_MULTIPLY_PER_HOUR"] = STEEMIT_APR_PERCENT_MULTIPLY_PER_HOUR;
            result["STEEMIT_APR_PERCENT_MULTIPLY_PER_ROUND"] = STEEMIT_APR_PERCENT_MULTIPLY_PER_ROUND;
            result["STEEMIT_APR_PERCENT_SHIFT_PER_BLOCK"] = STEEMIT_APR_PERCENT_SHIFT_PER_BLOCK;
            result["STEEMIT_APR_PERCENT_SHIFT_PER_HOUR"] = STEEMIT_APR_PERCENT_SHIFT_PER_HOUR;
            result["STEEMIT_APR_PERCENT_SHIFT_PER_ROUND"] = STEEMIT_APR_PERCENT_SHIFT_PER_ROUND;
            result["STEEMIT_BANDWIDTH_AVERAGE_WINDOW_SECONDS"] = STEEMIT_BANDWIDTH_AVERAGE_WINDOW_SECONDS;
            result["STEEMIT_BANDWIDTH_PRECISION"] = STEEMIT_BANDWIDTH_PRECISION;
            result["STEEMIT_BLOCKCHAIN_PRECISION"] = STEEMIT_BLOCKCHAIN_PRECISION;
            result["STEEMIT_BLOCKCHAIN_PRECISION_DIGITS"] = STEEMIT_BLOCKCHAIN_PRECISION_DIGITS;
            result["STEEMIT_BLOCKCHAIN_HARDFORK_VERSION"] = STEEMIT_BLOCKCHAIN_HARDFORK_VERSION;
            result["STEEMIT_BLOCKCHAIN_VERSION"] = STEEMIT_BLOCKCHAIN_VERSION;
            result["STEEMIT_BLOCK_INTERVAL"] = STEEMIT_BLOCK_INTERVAL;
            result["STEEMIT_BLOCKS_PER_DAY"] = STEEMIT_BLOCKS_PER_DAY;
            result["STEEMIT_BLOCKS_PER_HOUR"] = STEEMIT_BLOCKS_PER_HOUR;
            result["STEEMIT_BLOCKS_PER_YEAR"] = STEEMIT_BLOCKS_PER_YEAR;
            result["STEEMIT_CASHOUT_WINDOW_SECONDS"] = STEEMIT_CASHOUT_WINDOW_SECONDS;
            result["STEEMIT_CHAIN_ID"] = STEEMIT_CHAIN_ID;
            result["STEEMIT_CONTENT_APR_PERCENT"] = STEEMIT_CONTENT_APR_PERCENT;
            result["STEEMIT_CONVERSION_DELAY"] = STEEMIT_CONVERSION_DELAY;
            result["STEEMIT_CURATE_APR_PERCENT"] = STEEMIT_CURATE_APR_PERCENT;
            result["STEEMIT_DEFAULT_SBD_INTEREST_RATE"] = STEEMIT_DEFAULT_SBD_INTEREST_RATE;
            result["STEEMIT_FEED_HISTORY_WINDOW"] = STEEMIT_FEED_HISTORY_WINDOW;
            result["STEEMIT_FEED_INTERVAL_BLOCKS"] = STEEMIT_FEED_INTERVAL_BLOCKS;
            result["STEEMIT_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT"] = STEEMIT_FREE_TRANSACTIONS_WITH_NEW_ACCOUNT;
            result["STEEMIT_GENESIS_TIME"] = STEEMIT_GENESIS_TIME;
            result["STEEMIT_HARDFORK_REQUIRED_WITNESSES"] = STEEMIT_HARDFORK_REQUIRED_WITNESSES;
            result["STEEMIT_INIT_MINER_NAME"] = STEEMIT_INIT_MINER_NAME;
            result["STEEMIT_INIT_PUBLIC_KEY_STR"] = STEEMIT_INIT_PUBLIC_KEY_STR;
            result["STEEMIT_INIT_SUPPLY"] = STEEMIT_INIT_SUPPLY;
            result["STEEMIT_INIT_TIME"] = STEEMIT_INIT_TIME;
            result["STEEMIT_IRREVERSIBLE_THRESHOLD"] = STEEMIT_IRREVERSIBLE_THRESHOLD;
            result["STEEMIT_LIQUIDITY_APR_PERCENT"] = STEEMIT_LIQUIDITY_APR_PERCENT;
            result["STEEMIT_LIQUIDITY_REWARD_BLOCKS"] = STEEMIT_LIQUIDITY_REWARD_BLOCKS;
            result["STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC"] = STEEMIT_LIQUIDITY_REWARD_PERIOD_SEC;
            result["STEEMIT_LIQUIDITY_TIMEOUT_SEC"] = STEEMIT_LIQUIDITY_TIMEOUT_SEC;
            result["STEEMIT_MAX_ACCOUNT_NAME_LENGTH"] = STEEMIT_MAX_ACCOUNT_NAME_LENGTH;
            result["STEEMIT_MAX_ACCOUNT_WITNESS_VOTES"] = STEEMIT_MAX_ACCOUNT_WITNESS_VOTES;
            result["STEEMIT_MAX_ASSET_WHITELIST_AUTHORITIES"] = STEEMIT_MAX_ASSET_WHITELIST_AUTHORITIES;
            result["STEEMIT_MAX_AUTHORITY_MEMBERSHIP"] = STEEMIT_MAX_AUTHORITY_MEMBERSHIP;
            result["STEEMIT_MAX_BLOCK_SIZE"] = STEEMIT_MAX_BLOCK_SIZE;
            result["STEEMIT_MAX_CASHOUT_WINDOW_SECONDS"] = STEEMIT_MAX_CASHOUT_WINDOW_SECONDS;
            result["STEEMIT_MAX_COMMENT_DEPTH"] = STEEMIT_MAX_COMMENT_DEPTH;
            result["STEEMIT_MAX_FEED_AGE"] = STEEMIT_MAX_FEED_AGE;
            result["STEEMIT_MAX_INSTANCE_ID"] = STEEMIT_MAX_INSTANCE_ID;
            result["STEEMIT_MAX_MEMO_SIZE"] = STEEMIT_MAX_MEMO_SIZE;
            result["STEEMIT_MAX_WITNESSES"] = STEEMIT_MAX_WITNESSES;
            result["STEEMIT_MAX_MINER_WITNESSES"] = STEEMIT_MAX_MINER_WITNESSES;
            result["STEEMIT_MAX_PROXY_RECURSION_DEPTH"] = STEEMIT_MAX_PROXY_RECURSION_DEPTH;
            result["STEEMIT_MAX_RATION_DECAY_RATE"] = STEEMIT_MAX_RATION_DECAY_RATE;
            result["STEEMIT_MAX_RESERVE_RATIO"] = STEEMIT_MAX_RESERVE_RATIO;
            result["STEEMIT_MAX_RUNNER_WITNESSES"] = STEEMIT_MAX_RUNNER_WITNESSES;
            result["STEEMIT_MAX_SHARE_SUPPLY"] = STEEMIT_MAX_SHARE_SUPPLY;
            result["STEEMIT_MAX_SIG_CHECK_DEPTH"] = STEEMIT_MAX_SIG_CHECK_DEPTH;
            result["STEEMIT_MAX_TIME_UNTIL_EXPIRATION"] = STEEMIT_MAX_TIME_UNTIL_EXPIRATION;
            result["STEEMIT_MAX_TRANSACTION_SIZE"] = STEEMIT_MAX_TRANSACTION_SIZE;
            result["STEEMIT_MAX_UNDO_HISTORY"] = STEEMIT_MAX_UNDO_HISTORY;
            result["STEEMIT_MAX_URL_LENGTH"] = STEEMIT_MAX_URL_LENGTH;
            result["STEEMIT_MAX_VOTE_CHANGES"] = STEEMIT_MAX_VOTE_CHANGES;
            result["STEEMIT_MAX_VOTED_WITNESSES"] = STEEMIT_MAX_VOTED_WITNESSES;
            result["STEEMIT_MAX_WITHDRAW_ROUTES"] = STEEMIT_MAX_WITHDRAW_ROUTES;
            result["STEEMIT_MAX_WITNESS_URL_LENGTH"] = STEEMIT_MAX_WITNESS_URL_LENGTH;
            result["STEEMIT_MIN_ACCOUNT_CREATION_FEE"] = STEEMIT_MIN_ACCOUNT_CREATION_FEE;
            result["STEEMIT_MIN_ACCOUNT_NAME_LENGTH"] = STEEMIT_MIN_ACCOUNT_NAME_LENGTH;
            result["STEEMIT_MIN_BLOCK_SIZE_LIMIT"] = STEEMIT_MIN_BLOCK_SIZE_LIMIT;
            result["STEEMIT_MIN_CONTENT_REWARD"] = STEEMIT_MIN_CONTENT_REWARD;
            result["STEEMIT_MIN_CURATE_REWARD"] = STEEMIT_MIN_CURATE_REWARD;
            result["STEEMIT_MINER_ACCOUNT"] = STEEMIT_MINER_ACCOUNT;
            result["STEEMIT_MINER_PAY_PERCENT"] = STEEMIT_MINER_PAY_PERCENT;
            result["STEEMIT_MIN_FEEDS"] = STEEMIT_MIN_FEEDS;
            result["STEEMIT_MINING_REWARD"] = STEEMIT_MINING_REWARD;
            result["STEEMIT_MINING_TIME"] = STEEMIT_MINING_TIME;
            result["STEEMIT_MIN_LIQUIDITY_REWARD"] = STEEMIT_MIN_LIQUIDITY_REWARD;
            result["STEEMIT_MIN_LIQUIDITY_REWARD_PERIOD_SEC"] = STEEMIT_MIN_LIQUIDITY_REWARD_PERIOD_SEC;
            result["STEEMIT_MIN_PAYOUT_SBD"] = STEEMIT_MIN_PAYOUT_SBD;
            result["STEEMIT_MIN_POW_REWARD"] = STEEMIT_MIN_POW_REWARD;
            result["STEEMIT_MIN_PRODUCER_REWARD"] = STEEMIT_MIN_PRODUCER_REWARD;
            result["STEEMIT_MIN_RATION"] = STEEMIT_MIN_RATION;
            result["STEEMIT_MIN_TRANSACTION_EXPIRATION_LIMIT"] = STEEMIT_MIN_TRANSACTION_EXPIRATION_LIMIT;
            result["STEEMIT_MIN_TRANSACTION_SIZE_LIMIT"] = STEEMIT_MIN_TRANSACTION_SIZE_LIMIT;
            result["STEEMIT_MIN_UNDO_HISTORY"] = STEEMIT_MIN_UNDO_HISTORY;
            result["STEEMIT_NULL_ACCOUNT"] = STEEMIT_NULL_ACCOUNT;
            result["STEEMIT_NUM_INIT_MINERS"] = STEEMIT_NUM_INIT_MINERS;
            result["STEEMIT_POW_APR_PERCENT"] = STEEMIT_POW_APR_PERCENT;
            result["STEEMIT_PRODUCER_APR_PERCENT"] = STEEMIT_PRODUCER_APR_PERCENT;
            result["STEEMIT_PROXY_TO_SELF_ACCOUNT"] = STEEMIT_PROXY_TO_SELF_ACCOUNT;
            result["STEEMIT_SBD_INTEREST_COMPOUND_INTERVAL_SEC"] = STEEMIT_SBD_INTEREST_COMPOUND_INTERVAL_SEC;
            result["STEEMIT_SECONDS_PER_YEAR"] = STEEMIT_SECONDS_PER_YEAR;
            result["STEEMIT_REVERSE_AUCTION_WINDOW_SECONDS"] = STEEMIT_REVERSE_AUCTION_WINDOW_SECONDS;
            result["STEEMIT_START_MINER_VOTING_BLOCK"] = STEEMIT_START_MINER_VOTING_BLOCK;
            result["STEEMIT_START_VESTING_BLOCK"] = STEEMIT_START_VESTING_BLOCK;
            result["STEEMIT_SYMBOL"] = STEEMIT_SYMBOL;
            result["STEEMIT_TEMP_ACCOUNT"] = STEEMIT_TEMP_ACCOUNT;
            result["STEEMIT_UPVOTE_LOCKOUT"] = STEEMIT_UPVOTE_LOCKOUT;
            result["STEEMIT_VESTING_WITHDRAW_INTERVALS"] = STEEMIT_VESTING_WITHDRAW_INTERVALS;
            result["STEEMIT_VESTING_WITHDRAW_INTERVAL_SECONDS"] = STEEMIT_VESTING_WITHDRAW_INTERVAL_SECONDS;
            result["STEEMIT_VOTE_CHANGE_LOCKOUT_PERIOD"] = STEEMIT_VOTE_CHANGE_LOCKOUT_PERIOD;
            result["STEEMIT_VOTE_REGENERATION_SECONDS"] = STEEMIT_VOTE_REGENERATION_SECONDS;
            result["STEEM_SYMBOL"] = STEEM_SYMBOL_NAME;
            result["VESTS_SYMBOL"] = VESTS_SYMBOL;
            result["BLOCKCHAIN_NAME"] = BLOCKCHAIN_NAME;
            result["STEEMIT_ADDRESS_PREFIX"] = STEEMIT_ADDRESS_PREFIX;

            return result;
        }

    }
} // steemit::protocol