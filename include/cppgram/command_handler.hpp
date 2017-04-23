#ifndef CPPGRAM_COMMAND_HANDLER_HPP
#define CPPGRAM_COMMAND_HANDLER_HPP

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

namespace cppgram
{
class BasicBot;
enum EUpdate : short;

namespace commands
{
class Command;
}

namespace types
{
class Update;
}

class CommandHandler
{
    friend class BasicBot;

    public:
    CommandHandler( BasicBot *bot );
    CommandHandler( BasicBot *bot, const CommandHandler &c );
    CommandHandler( const CommandHandler &c );
    CommandHandler operator=( const CommandHandler &c );

    void addCommand( commands::Command* new_command );
    void setCommands( const CommandHandler &c );

    private:
    bool processCommands( const types::Update &update );

    BasicBot *owner;
    std::unordered_map<const EUpdate, std::vector<commands::Command*>>
            commands;
};
}

#endif
