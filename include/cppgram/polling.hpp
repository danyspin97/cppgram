#ifndef __CPPGRAM_POLLING_HPP
#define __CPPGRAM_POLLING_HPP

#include "concurrentqueue/blockingconcurrentqueue.h"
#include "cppgram/basic_bot.hpp"

namespace cppgram
{
template <class T> class Polling
{
    public:
    Polling( T             bot,
             uint_fast8_t  threads_number,
             uint_fast32_t limit   = 100,
             uint_fast32_t timeout = 60 );
    Polling( std::vector<T> bots, uint_fast32_t limit = 100, uint_fast32_t timeout = 60 );

    void run();

    private:
    uint_fast32_t firstUpdateID( T& poller );
    void runMultithread();
    void runSinglethread();
    void setThreadAffinity( std::vector<std::thread> &threads );
    void loopBot( T bot );
    void initLogging();

    std::vector<T>                                       bots;
    moodycamel::BlockingConcurrentQueue<cppgram::Update> updates_queue;
    moodycamel::ProducerToken                            producer_token;
    std::shared_ptr<spdlog::logger>                      console_stderr;
    std::shared_ptr<spdlog::logger>                      console_stdout;

    uint_fast32_t limit;
    uint_fast32_t timeout;
};
}

#include "polling_templates.hpp"

#endif
