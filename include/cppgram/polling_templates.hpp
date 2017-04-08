#include <thread>

#include "polling.hpp"

template <class T> cppgram::Polling<T>::Polling( T bot, u_int8_t threads_number )
{
    bots = std::vector<T>( threads_number, bot );
}

template <class T>
cppgram::Polling<T>::Polling( std::vector<T> bots )
    : bots( bots )
{
}

template <class T>
void
cppgram::Polling<T>::run()
{
    uint_fast8_t size = bots.size();
    if ( size == 0 )
    {
        return;
    }

    initLogging();

    if ( size == 1 )
    {
        runSinglethread();
    }

    runMultithread();
}

template <class T>
void
cppgram::Polling<T>::runMultithread()
{
    T poller = bots.back();
    bots.pop_back();
    std::vector<std::thread> threads;
    for ( T &bot : bots )
    {
        threads.push_back( std::thread( &Polling::loopBot, this, bot ) );
    }

    setThreadAffinity( threads );

    std::vector<Update> updates;
    uint_fast32_t       updates_offset = firstUpdateID( poller );
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

    for ( std::thread &t : threads )
    {
        t.join();
    }
}

template <class T>
void
cppgram::Polling<T>::runSinglethread()
{
}

template <class T>
void
cppgram::Polling<T>::setThreadAffinity( std::vector<std::thread> &threads )
{
}

template <class T>
void
cppgram::Polling<T>::loopBot( T bot )
{
    cppgram::Update new_update;
    while ( 1 )
    {
        updates_queue.wait_dequeue( new_update );
        bot.processUpdate( std::move( new_update ) );
    }
}

template <class T>
uint_fast32_t
cppgram::Polling<T>::firstUpdateID( T &poller )
{
    std::vector<Update> first_update;
    while ( !poller.getUpdates( first_update, 0, 1 ) )
        ;
    return first_update[0].update_id;
}

template <class T>
void
cppgram::Polling<T>::initLogging()
{
    spdlog::set_async_mode( 4096 );
    auto sink = std::make_shared<spdlog::sinks::simple_file_sink_mt>( "bot.log" );
    for ( auto bot : bots )
    {
        if ( bot.sink == nullptr )
        {
            bot.sink   = sink;
            bot.logger = std::make_shared<spdlog::logger>( "BotLog", sink );
        }
    }
}
