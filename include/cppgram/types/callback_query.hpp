#ifndef CPPGRAM_CALLBACK_QUERY_HPP
#define CPPGRAM_CALLBACK_QUERY_HPP

#include <string>

#include <json/json.h>

#include "message.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief Data from an inline keyboard button pressed.
 * \details This object represents an incoming callback query from a callback button in an inline
 * keyboard. (https://core.telegram.org/bots/api#callbackquery) */
class CallbackQuery
{
    /** @} */

    public:
    /** \brief Unique identifier for this query */
    std::string id;

    /** \brief Sender */
    User from;

    /** \brief <i>Optional</i>. Message with the callback button that originated the query.
     * \details Note that message content and message date will not be available if the message is
     * too old */
    std::experimental::optional<Message> message;

    /** \brief <i>Optional</i>. Identifier of the message sent via the bot in inline mode, that
     * originated the query */
    std::experimental::optional<std::string> inline_message_id;

    /** \brief Identifier, uniquely corresponding to the chat to which the message with the callback
     * button was sent.
     * \details Useful for high scores in [games](https://core.telegram.org/bots/api/#games). */
    std::string chat_instance;

    /** \brief <i>Optional</i>. Data associated with the callback button.
     * \details Be aware that a bad client can send arbitrary data in this field */
    std::experimental::optional<std::string> data,

            /** \brief <i>Optional</i>. Short name of a
               [Game](https://core.telegram.org/bots/api/#games) to be returned, serves as the
               unique
               identifier for the game */
            game_short_name;

    CallbackQuery( Json::Value &json_callback_query )
        : id( json_callback_query["id"].asString() )
        , from( json_callback_query["from"] )
        , chat_instance( json_callback_query["chat_instance"].asString() )
    {
        if ( !json_callback_query["message"].isNull() )
        {
            message.emplace( Message( json_callback_query["message"] ) );
        }

        if ( !json_callback_query["inline_message_id"].isNull() )
        {
            inline_message_id.emplace( json_callback_query["inline_message_id"].asString() );
        }

        if ( !json_callback_query["data"].isNull() )
        {
            data.emplace( json_callback_query["data"].asString() );
        }

        if ( !json_callback_query["game_short_name"].isNull() )
        {
            game_short_name.emplace( json_callback_query["game_short_name"].asString() );
        }
    }
};
}
}

#endif
