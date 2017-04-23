#ifndef CPPGRAM_MESSAGE_COMMAND_HPP
#define CPPGRAM_MESSAGE_COMMAND_HPP

#include "command.hpp"
#include "cppgram/types/update.hpp"

namespace cppgram
{
namespace commands
{
typedef std::function<void( class BasicBot &, const types::Message )> MessageClosure;

class MessageCommand : public Command
{
    public:
    const EUpdate type = EUpdate::eMessage;
    std::string          command;
    MessageClosure       script;

    MessageCommand( std::string &command, MessageClosure script )
        : command( "/" + command )
        , script( script )
    {
    }

    virtual void callClosure( BasicBot &bot, const types::Update &update )
    {
        bot.setChatID(update.message->chat.id);
        script( bot, update.message.value() );
    }

    virtual bool isValid( const types::Update &update )
    {
        // If there is at least a command in the message
        bool is_command = update.message->entities.size() != 0;

        // and the command is found in the message
        if ( is_command && update.message->text->find( command ) != std::string::npos)
        {
            return true;
        }

        return false;
    }
};
}
}

#endif
