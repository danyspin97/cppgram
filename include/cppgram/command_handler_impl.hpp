#include "cppgram/command_handler.hpp"
#include "cppgram/commands/command.hpp"
#include "cppgram/types/update.hpp"

using cppgram::CommandHandler;
using cppgram::BasicBot;

using cppgram::types::Update;

using cppgram::commands::Command;

template <class T>
CommandHandler<T>::CommandHandler()
    : owner( nullptr )
{
}

template <class T>
CommandHandler<T>::CommandHandler( T *bot )
    : owner( bot )
{
}

template <class T>
CommandHandler<T>::CommandHandler( T *bot, const CommandHandler &c )
    : owner( bot )
    , commands( c.commands )
{
}

template <class T>
CommandHandler<T>::CommandHandler( const CommandHandler &c )
    : owner( c.owner )
    , commands( c.commands )
{
}

template <class T>
CommandHandler<T> &
CommandHandler<T>::operator=( const CommandHandler &c )
{
    // There is no owner as two CommandHandler objects cannot share the same owner
    owner    = nullptr;
    commands = c.commands;

    return *this;
}

template <class T>
CommandHandler<T> &
CommandHandler<T>::operator=( CommandHandler &&c )
{
    owner    = std::move( c.owner );
    commands = std::move( c.commands );

    return *this;
}

template <class T>
void
CommandHandler<T>::addCommand( Command<T> *new_command )
{
    commands[new_command->type].push_back( new_command );
}

template <class T>
void
CommandHandler<T>::setCommands( const CommandHandler &c )
{
    commands = c.commands;
}

template <class T>
void
CommandHandler<T>::init( T *bot )
{
    if ( !owner )
    {
        owner = bot;
    }
}

template <class T>
bool
CommandHandler<T>::processCommands( const Update &update )
{
    // For each command (valid for the current update)
    for ( Command<T> *c : commands[update.type] )
    {
        if ( c->isValid( update ) )
        {
            c->callClosure( *owner, update );
            return true;
        }
    }

    return false;
}
