#ifndef CPPGRAM_CALLBACK_QUERY_H
#define CPPGRAM_CALLBACK_QUERY_H

#include <string>

#include <json/json.h>

#include "user.h"
#include "message.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Data from an inline keyboard button pressed.
 * \details This object represents an incoming callback query from a callback button in an inline keyboard. (https://core.telegram.org/bots/api#callbackquery) */
struct callbackQuery
{
    /** @} */

    /** \brief Unique identifier for this query */
    std::string id;

    /** \brief Sender */
    cppgram::user from;

    /** \brief <i>Optional</i>. Message with the callback button that originated the query.
     * \details Note that message content and message date will not be available if the message is too old */
    std::experimental::optional<cppgram::message> message;

    /** \brief <i>Optional</i>. Identifier of the message sent via the bot in inline mode, that originated the query */
    std::experimental::optional<std::string> inline_message_id;

    /** \brief Identifier, uniquely corresponding to the chat to which the message with the callback button was sent.
     * \details Useful for high scores in [games](https://core.telegram.org/bots/api/#games). */
    std::string chat_instance;

    /** \brief <i>Optional</i>. Data associated with the callback button.
     * \details Be aware that a bad client can send arbitrary data in this field */
    std::experimental::optional<std::string> data,

    /** \brief <i>Optional</i>. Short name of a [Game](https://core.telegram.org/bots/api/#games) to be returned, serves as the unique identifier for the game */
            game_short_name;

    callbackQuery(Json::Value &jsonCallbackQuery)
        : id(jsonCallbackQuery["id"].asString()),
          from(jsonCallbackQuery["from"]),
          chat_instance(jsonCallbackQuery["chat_instance"].asString())
    {

        message.emplace(jsonCallbackQuery["message"]);

        inline_message_id.emplace(jsonCallbackQuery["inline_message_id"].asString());

        data.emplace(jsonCallbackQuery["data"].asString());

        game_short_name.emplace(jsonCallbackQuery["game_short_name"].asString());

    }

    callbackQuery()
    {}

};

}

#endif //CPPGRAM_CALLBACK_QUERY_H


