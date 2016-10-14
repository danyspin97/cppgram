#ifndef CPPGRAM_UPDATE_H
#define CPPGRAM_UPDATE_H

#include <string>

#include <json/json.h>

#include "message.h"
#include "inline_query.h"
#include "choosen_inline_result.h"
#include "callback_query.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

struct update
{
    /** @} */

    enum UpdateType type;

    union
    {
        struct message *message;

        struct message *editedMessage;

        struct inlineQuery *inlineQuery;

        struct choosenInlineResult *choosenInlineResult;

        struct callbackQuery *callbackQuery;
    };

    update(Json::Value &jsonUpdate)
    {
        if (!jsonUpdate["message"].isNull())
        {
            type = UpdateType::Message;
            message = new struct message(jsonUpdate["message"]);
        }
        else if (!jsonUpdate["callback_query"].isNull())
        {
            type = UpdateType::CallbackQuery;
            callbackQuery = new struct callbackQuery(jsonUpdate["callback_query"]);
        }
        else if (!jsonUpdate["edited_message"].isNull())
        {
            type = UpdateType::EditedMessage;
            message = new struct message(jsonUpdate["edited_message"]);
        }
        else if (!jsonUpdate["inline_query"].isNull())
        {
            type = UpdateType::InlineQuery;
            inlineQuery = new struct inlineQuery(jsonUpdate["inline_query"]);
        }
        else if (!jsonUpdate["choosen_inline_result"].isNull())
        {
            type = UpdateType::ChoosenInlineResult;
            choosenInlineResult = new struct choosenInlineResult(jsonUpdate["choosen_inline_result"]);
        }
    }

    ~update()
    {};

    update()
    {};
};

}

#endif //CPPGRAM_UPDATE_H
