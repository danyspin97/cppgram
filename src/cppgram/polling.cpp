#include <thread>

#include "cppgram/polling.hpp"

using cppgram::Polling;
using cppgram::BasicBot;

Polling::Polling( std::string &token, std::vector<cppgram::BasicBot> &bots )
    : bots( bots )
{
    for ( auto &bot : bots )
    {
        bot.setToken( token );
    }
}

void
Polling::run()
{
    auto size = bots.size();
    if ( size == 0 )
    {
        return;
    }
    auto &poller = bots.back();
    bots.pop_back();
    std::vector<std::thread> threads(size - 1);
    for ( auto i = 0; i < size - 2; ++i )
    {
        //threads[i] = std::thread( &Polling::activeBot, bots[i] );
    }

    Json::Value updates;
    while ( 1 )
    {
        poller.getUpdates( updates );
        for ( auto update : updates )
        {
            updates_queue.try_enqueue( update );
        }
    }

    for ( auto &thread : threads )
    {
        thread.join();
    }
}

void
Polling::activeBot( BasicBot &bot )
{
    cppgram::Update new_update;
    while ( 1 )
    {
        updates_queue.wait_dequeue( new_update );
        bot.processUpdate( new_update );
    }
}
