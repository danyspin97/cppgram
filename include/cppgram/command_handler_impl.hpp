#include "cppgram/command_handler.hpp"
#include "cppgram/commands/command.hpp"
#include "cppgram/types/update.hpp"

using cppgram::CommandHandler;
using cppgram::BasicBot;

using cppgram::types::Update;

using cppgram::commands::Command;

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
CommandHandler<T>
CommandHandler<T>::operator=( const CommandHandler &c )
{
    owner    = c.owner;
    commands = c.commands;

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
