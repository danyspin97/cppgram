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
    struct user *from;

    /** \brief <i>Optional</i>. Message with the callback button that originated the query.
     * \details Note that message content and message date will not be available if the message is too old */
    struct message *message;

    /** \brief <i>Optional</i>. Identifier of the message sent via the bot in inline mode, that originated the query */
    std::string inline_message_id;

    /** \brief Data associated with the callback button.
     * \details Be aware that a bad client can send arbitrary data in this field */
    std::string data;

    callbackQuery(Json::Value &jsonCallbackQuery) : id(jsonCallbackQuery["id"].asString()),
        from(new struct user(jsonCallbackQuery["from"])),
        data(jsonCallbackQuery["data"].asString())
    {
        message = !jsonCallbackQuery["message"].isNull() ? new struct message(jsonCallbackQuery["message"]) : nullptr;

        inline_message_id = (!jsonCallbackQuery["inline_message_id"].isNull()) ? jsonCallbackQuery["inline_message_id"].asUInt() : int_fast32_t();
    }

    ~callbackQuery()
    {
        delete from;
        delete message;
    }

    callbackQuery()
    {}

    callbackQuery(const callbackQuery &prev)
    {
        from = prev.from;
        message = prev.message;

        id = prev.id;
        inline_message_id = prev.inline_message_id;
        data = prev.data;
    }
};

}

#endif //CPPGRAM_CALLBACK_QUERY_H


