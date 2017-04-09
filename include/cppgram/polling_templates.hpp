#include <thread>

#include "polling.hpp"

template <class T>
cppgram::Polling<T>::Polling( T             bot,
                              uint_fast8_t  threads_number,
                              uint_fast32_t limit,
                              uint_fast32_t timeout )
    : limit( limit )
    , timeout( timeout )
    , updates_queue( 150 )
    , producer_token( updates_queue )
{
    bots           = std::vector<T>( threads_number, bot );
    console_stdout = spdlog::stdout_color_mt( "console" );
    console_stderr = spdlog::stderr_color_mt( "error_console" );
}

template <class T>
cppgram::Polling<T>::Polling( std::vector<T> bots, uint_fast32_t limit, uint_fast32_t timeout )
    : bots( bots )
    , limit( limit )
    , timeout( timeout )
    , updates_queue( 150 )
    , producer_token( updates_queue )
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

    console_stdout->info( "Bots started." );
    std::vector<Update> updates;
    uint_fast32_t       updates_offset = firstUpdateID( poller );
    while ( 1 )
    {
        uint_fast32_t count;
        if ( poller.getUpdates( updates, updates_offset ) )
        {
            count = updates.size();
            updates_queue.enqueue_bulk( producer_token, updates.begin(), count );
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
    console_stdout->info( "Bots started." );
    auto          bot            = bots.back();
    uint_fast32_t updates_offset = firstUpdateID( bot );
    while ( 1 )
    {
        std::vector<Update> updates;
        if ( bot.getUpdates( updates, updates_offset ) )
        {
            for ( auto update : updates )
            {
                bot.processUpdate( std::move( update ) );
            }
            updates_offset += updates.size();
            updates.clear();
        }
    }
}

template <class T>
void
cppgram::Polling<T>::setThreadAffinity( std::vector<std::thread> &threads )
{
    u_int8_t cores = std::thread::hardware_concurrency();
    if ( threads.size() <= cores )
    {
        for ( auto i = 0; i < threads.size(); i++ )
        {
            cpu_set_t cpuset;
            CPU_ZERO( &cpuset );
            CPU_SET( i, &cpuset );
            int rc = pthread_setaffinity_np(
                    threads[i].native_handle(), sizeof( cpu_set_t ), &cpuset );
            if ( rc != 0 )
            {
                console_stderr->critical( "Error calling pthread_setaffinity_np: "
                                          + std::to_string( rc ) );
            }
        }
        console_stdout->info( "Thread affinity per cpu set." );
    }
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
    return first_update[0].update_id -1 ;
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
