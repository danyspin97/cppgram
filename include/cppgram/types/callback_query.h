#ifndef CPPGRAM_CALLBACK_QUERY_H
#define CPPGRAM_CALLBACK_QUERY_H

#include <string>

#include <json/json.h>

#include "integers.h"
#include "user.h"
#include "message.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

struct callbackQuery
{
    /** @} */
    std::string id;
    struct user *from;
    struct message *message;
    std::string inline_message_id;
    std::string data;

    callbackQuery(Json::Value &callbackQuery) : id(callbackQuery["id"].asString()),
                                                from(new struct user(callbackQuery["from"])),
                                                message(new struct message(callbackQuery["message"])),
                                                inline_message_id(callbackQuery["inline_message_id"].asString()),
                                                data(callbackQuery["data"].asString())
    {}

    ~callbackQuery()
    {
        delete from;
        delete message;
    }

    callbackQuery()
    {}

    callbackQuery(const callbackQuery &prev)
    {
        *from = *(prev.from);
        //*message = *(prev.message);

        id = prev.id;
        inline_message_id = prev.inline_message_id;
        data = prev.data;
    }
};

}

#endif //CPPGRAM_CALLBACK_QUERY_H
