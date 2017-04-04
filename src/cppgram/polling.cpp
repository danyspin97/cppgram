// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <thread>

#include "cppgram/polling.hpp"

using cppgram::Polling;
using cppgram::BasicBot;

Polling::Polling( std::vector<cppgram::BasicBot> bots )
    : bots( bots )
{
}

void
Polling::run()
{
    auto size = bots.size();
    if ( size == 0 )
    {
        return;
    }
    auto poller = bots.back();
    bots.pop_back();
    std::vector<std::thread> threads;
    for ( auto bot : bots )
    {
        threads.push_back( std::thread( &Polling::activeBot, this, &bot ) );
    }

    std::vector<Update> updates;
    uint_fast32_t       updates_offset = firstUpdateID( &poller );
    while ( 1 )
    {
        uint_fast32_t count;
        if ( poller.getUpdates( updates, updates_offset ) )
        {
            count = updates.size();
            updates_queue.enqueue_bulk( updates.begin(), count );
            updates_offset += count;
            updates.clear();
        }
    }

    for ( auto &thread : threads )
    {
        thread.join();
    }
}

void
Polling::activeBot( BasicBot *bot )
{
    cpr::Session connection;
    bot->setConnection( &connection );
    cppgram::Update new_update;
    while ( 1 )
    {
         updates_queue.wait_dequeue( new_update );
         bot->processUpdate( new_update );
    }
}

uint_fast32_t
Polling::firstUpdateID( BasicBot *poller )
{
    std::vector<Update> first_update;
    while ( !poller->getUpdates( first_update, 0, 1 ) )
        ;
    return first_update[0].update_id;
}
