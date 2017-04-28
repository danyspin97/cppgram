#ifndef CPPGRAM_MESSAGE_COMMAND_HPP
#define CPPGRAM_MESSAGE_COMMAND_HPP

#include "command.hpp"
#include "cppgram/types/update.hpp"

namespace cppgram
{
namespace commands
{
typedef std::function<void( class BasicBot &, const types::Message )> MessageClosure;

/**
 * @brief Triggered by bot command in messages.
 * @details If the message contains a bot command and it is the same as this command, call the
 * underlying function.
 * This command will be triggered only if the command is the first to appear in the message.
 */
class MessageCommand : public Command
{
    public:
    /**
     * @brief Construct a message command.
     * @param command String that has to appear in the bot command to trigger this object.
     * If you want the bot to trigger on the command /start, pass "start" as command parameter.
     * @param script The function that will be called if this command is triggered.
     */
    MessageCommand( std::string &command, MessageClosure script )
        : command( "/" + command )
        , script( script )
    {
    }

    /**
     * @internal
     * @brief Forward the update to the script that will process it.
     * @param bot Object that will process the update.
     * @param update Update to process.
     */
    virtual void callClosure( BasicBot &bot, const types::Update &update )
    {
        bot.setChatId( update.message->chat.id );
        script( bot, update.message.value() );
    }

    /**
     * @internal
     * @brief Check if the message received has a bot command and it is the same as the string
     * command.
     * @param update Update to check.
     * @return True if the update triggered this command.
     */
    virtual bool isValid( const types::Update &update )
    {
        // If there isn't at least a command in the message
        if ( update.message->entities.size() == 0 )
        {
            return false;
        }

        types::MessageEntity entity = update.message->entities[0];

        // If the first entity is not a bot_command
        if ( entity.type != EMessageEntity::bot_command )
        {
            return false;
        }

        // If the command is not the first text in the message
        if ( entity.offset != 0 )
        {
            return false;
        }

        // Get the string that corresponds to the bot_command
        std::string entity_text = update.message->text->substr( 0, entity.length );

        // and the command is found in the message
        if ( entity_text.find( command ) != std::string::npos )
        {
            return true;
        }

        return false;
    }

    private:
    /** @internal @brief Triggered only by Message type updates. */
    const EUpdate type = EUpdate::eMessage;

    /** @internal @brief String of the bot command that will trigger this object. */
    std::string command;

    /** @internal @brief Function which the update will be forwared to. */
    MessageClosure script;
};
}
}

#endif
