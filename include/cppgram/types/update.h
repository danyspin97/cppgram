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

    std::experimental::optional<struct message> message;

    std::experimental::optional<struct message> editedMessage;

    std::experimental::optional<struct inlineQuery> inlineQuery;

    std::experimental::optional<struct choosenInlineResult> choosenInlineResult;

    std::experimental::optional<struct callbackQuery> callbackQuery;

    update(Json::Value &jsonUpdate)
    {
        if (!jsonUpdate["message"].isNull())
        {
            type = UpdateType::Message;
            message.emplace(cppgram::message(jsonUpdate["message"]));
        }
        else if (!jsonUpdate["callback_query"].isNull())
        {
            type = UpdateType::CallbackQuery;
            callbackQuery.emplace(cppgram::callbackQuery(jsonUpdate["callback_query"]));
        }
        else if (!jsonUpdate["edited_message"].isNull())
        {
            type = UpdateType::EditedMessage;
            editedMessage.emplace(cppgram::message(jsonUpdate["edited_message"]));
        }
        else if (!jsonUpdate["inline_query"].isNull())
        {
            type = UpdateType::InlineQuery;
            inlineQuery.emplace(cppgram::inlineQuery(jsonUpdate["inline_query"]));
        }
        else if (!jsonUpdate["choosen_inline_result"].isNull())
        {
            type = UpdateType::ChoosenInlineResult;
            choosenInlineResult.emplace(cppgram::choosenInlineResult(jsonUpdate["choosen_inline_result"]));
        }
    }

    ~update()
    {};

    update()
    {};

    const update& operator= (const update& u)
    {

        if (&u != this) {

            type = u.type;

            message = u.message;

            callbackQuery = u.callbackQuery;

            editedMessage = u.editedMessage;

            choosenInlineResult = u.choosenInlineResult;

            inlineQuery = u.inlineQuery;

        }

        return *this;

    };

    update& operator= (update& u) {

        if (&u != this) {

            type = u.type;

            message = u.message;

            callbackQuery = u.callbackQuery;

            editedMessage = u.editedMessage;

            choosenInlineResult = u.choosenInlineResult;

            inlineQuery = u.inlineQuery;

        }

        return *this;

    };

};

}

#endif //CPPGRAM_UPDATE_H
