#include "cppgram/command_handler.hpp"
#include "cppgram/commands/command.hpp"
#include "cppgram/types/update.hpp"

using cppgram::CommandHandler;
using cppgram::BasicBot;

using cppgram::types::Update;

using cppgram::commands::Command;

CommandHandler::CommandHandler( BasicBot *bot )
    : owner( bot )
{
}

CommandHandler::CommandHandler( BasicBot *bot, const CommandHandler &c )
    : owner( bot )
    , commands( c.commands )
{
}

CommandHandler::CommandHandler( const CommandHandler &c )
    : owner( c.owner )
    , commands( c.commands )
{
}

CommandHandler
CommandHandler::operator=( const CommandHandler &c )
{
    owner    = c.owner;
    commands = c.commands;

    return *this;
}

void
CommandHandler::addCommand( Command* new_command )
{
    commands[new_command->type].push_back( new_command );
}

void
CommandHandler::setCommands( const CommandHandler &c )
{
    commands = c.commands;
}

bool
CommandHandler::processCommands( const Update &update )
{
    // For each command (valid for the current update)
    for ( Command* c : commands[update.type] )
    {
        if (c->isValid(update))
        {
            c->callClosure(*owner, update);
            return true;
        }
    }

    return false;
}
