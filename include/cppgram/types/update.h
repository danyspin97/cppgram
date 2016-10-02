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

    update(Json::Value &update)
    {
        if (!update["message"].isNull())
        {
            type = UpdateType::Message;
            message = new struct message(update["message"]);
        } else if (!update["callback_query"].isNull())
        {
            type = UpdateType::CallbackQuery;
            callbackQuery = new struct callbackQuery(update["callback_query"]);
        } else if (!update["edited_message"].isNull())
        {
            type = UpdateType::EditedMessage;
            message = new struct message(update["edited_message"]);
        } else if (!update["inline_query"].isNull())
        {
            type = UpdateType::InlineQuery;
            inlineQuery = new struct inlineQuery(update["inline_query"]);
        } else if (!update["choosen_inline_result"].isNull())
        {
            type = UpdateType::ChoosenInlineResult;
            choosenInlineResult = new struct choosenInlineResult(update["choosen_inline_result"]);
        }
    }

    ~update()
    {};

    update()
    {};
};

}

#endif //CPPGRAM_UPDATE_H
