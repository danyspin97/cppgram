#ifndef __CPPGRAM_POLLING_HPP
#define __CPPGRAM_POLLING_HPP

#include "concurrentqueue/blockingconcurrentqueue.h"
#include "cppgram/basic_bot.hpp"

namespace cppgram
{
/**
 * @brief Handle long (or short) polling for a bot.
 */
template <class T> class Polling
{
    public:
    /**
     * @brief Create a polling object by passing a single bot, and the number of threads.
     * @param bot Bot that will handle updates.
     * @param threads_number Number of threads that will run asynchronously.
     * @param limit Limits the number of updates to be retrieved. Values between 1—100 are
     * accepted.
     * @param timeout Timeout in seconds for long polling. Defaults to 0, i.e. usual short
     * polling.
     */
    Polling( T             bot,
             uint_fast8_t  threads_number,
             uint_fast32_t limit   = 100,
             uint_fast32_t timeout = 60 );

    /**
     * @brief Create a polling object by passing a vector of bots of the same type.
     * @param bots Vector of bots that will run asynchronously.
     * @param limit Limits the number of updates to be retrieved. Values between 1—100 are
     * accepted.
     * @param timeout Timeout in seconds for long polling. Defaults to 0, i.e. usual short
     * polling.
     */
    Polling( std::vector<T> bots, uint_fast32_t limit = 100, uint_fast32_t timeout = 60 );

    /**
     * @brief Start the polling.
     */
    void run();

    private:
    /**
     * @brief Get the offset of the first update to process.
     * @return Update offset.
     */
    uint_fast32_t firstUpdateID( T &poller );

    /**
     * @internal
     * @brief Start the bot asynchronously.
     */
    void runMultithread();

    /**
     * @internal
     * @brief Start a bot in one thread.
     */
    void runSinglethread();

    /**
     * @internal
     * @brief Assign each thread to a core.
     */
    void setThreadAffinity( std::vector<std::thread> &threads );

    /**
     * @internal
     * @brief Take an update and forward it to a bot that will process it.
     * @details Wait until there is an update, then let the bot process it.
     * This method will be passed to a thread and cycle until the programs stops.
     * @param bot Object that will process the update.
     */
    void loopBot( T bot );

    /**
     * @interal
     * @brief Init logger for each bot.
     */
    void initLogging();

    /** @brief Vector of bots. */
    std::vector<T> bots;

    /** @brief Queue of the updates to process. */
    moodycamel::BlockingConcurrentQueue<types::Update> updates_queue;

    /** @brief Logger that will print error messages to the console */
    std::shared_ptr<spdlog::logger> console_stderr;

    /** @brief Logger that will print messages to the console. */
    std::shared_ptr<spdlog::logger> console_stdout;

    /**
     * @internal
     * @brief Number of the updates that will be requested each call of getUpdates.
     * @details Set in the constructor.
     */
    uint_fast32_t limit;

    /**
     * @internal
     * @brief Seconds between each call of getUpdates.
     * @details Set in the constructor.
     */
    uint_fast32_t timeout;
};
}

#include "polling_impl.hpp"

#endif
