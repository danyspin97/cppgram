#ifndef __CPPGRAM_POLLING_HPP
#define __CPPGRAM_POLLING_HPP

#include "concurrentqueue/blockingconcurrentqueue.h"
#include "cppgram/basic_bot.hpp"

namespace cppgram
{
class Polling
{
    public:
    Polling(){};

    Polling( std::vector<cppgram::BasicBot> bots );

    void run();

    void activeBot( cppgram::BasicBot *bot );

    private:
    uint_fast32_t firstUpdateID( BasicBot *poller );

    std::vector<cppgram::BasicBot> bots;

    moodycamel::BlockingConcurrentQueue<cppgram::Update> updates_queue;
};
}

#endif
