#ifndef CPPGRAM_COMMAND_HPP
#define CPPGRAM_COMMAND_HPP

#include <functional>
#include <string>

#include "cppgram/basic_bot.hpp"
#include "cppgram/types/enums.hpp"

namespace cppgram
{
namespace types
{
class Update;
}

namespace commands
{
/**
 * @brief Abstract class for bot commands.
 * @details Command that will be triggered when some conditions are met in the current update.
 * Inherit this class to implements behavior and condition that have to be met before triggering
 * the command.
 */
class Command
{
    public:
    /** @brief type of the update for which the command will be triggered. */
    const EUpdate type;

    Command()
        : type( EUpdate::eMessage )
    {
    }

    /**
     * @brief Forward the update to another function.
     * @details When the update triggers this command, the current update will be forwarded to this
     * method.
     * Call the underlying pointer to a function using this method.
     * Set also bot data(`chat_id`, `inline_query_id`, `callback_query_id`) or some api methods will
     * not work.
     */
    virtual void callClosure( BasicBot &, const types::Update & ) = 0;

    /**
     * @brief Does the update trigger this command?
     * @param update Current update to parse.
     * @return True if the current update triggered the command.
     */
    virtual bool isValid( const types::Update & ) = 0;

    protected:
    /**
     * @brief Set the inline query id of the bot for using AnswerInlineQuery.
     * @param inline_query_id The id of the inline query received.
     * @param bot Bot that is processing the update.
     */
    void setInlineQueryId( std::string &inline_query_id, BasicBot &bot )
    {
        bot.inline_query_id = inline_query_id;
    }

    /**
     * @brief Set the callback query id the current update.
     * @param callback_query_id Id of the callback query received.
     * @param bot Bot that is processing the update.
     */
    void setCallbackQueryId( std::string &callback_query_id, BasicBot &bot )
    {
        bot.callback_query_id = callback_query_id;
    }
};
}
}

#endif
