#ifndef CPPGRAM_UPDATE_H
#define CPPGRAM_UPDATE_H

#include <string>

#include <json/json.h>

#include "cppgram/types/callback_query.h"
#include "cppgram/types/choosen_inline_result.h"
#include "cppgram/types/inline_query.h"
#include "cppgram/types/message.h"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

struct update
{
    /** @} */

    enum UpdateType type;

    std::experimental::optional<cppgra::message> message;

    std::experimental::optional<cppgram::message> edited_message;

    std::experimental::optional<cppgram::inlineQuery> inline_query;

    std::experimental::optional<cppgram::choosenInlineResult> choosen_inline_result;

    std::experimental::optional<cppgram::callbackQuery> callback_query;

    update( Json::Value &jsonUpdate )
    {
        if ( !jsonUpdate["message"].isNull() )
        {
            type = UpdateType::Message;
            message.emplace( cppgram::message( jsonUpdate["message"] ) );
        }
        else if ( !jsonUpdate["callback_query"].isNull() )
        {
            type = UpdateType::CallbackQuery;
            callback_query.emplace( cppgram::callbackQuery( jsonUpdate["callback_query"] ) );
        }
        else if ( !jsonUpdate["edited_message"].isNull() )
        {
            type = UpdateType::EditedMessage;
            edited_message.emplace( cppgram::message( jsonUpdate["edited_message"] ) );
        }
        else if ( !jsonUpdate["inline_query"].isNull() )
        {
            type = UpdateType::InlineQuery;
            inline_query.emplace( cppgram::inlineQuery( jsonUpdate["inline_query"] ) );
        }
        else if ( !jsonUpdate["choosen_inline_result"].isNull() )
        {
            type = UpdateType::ChoosenInlineResult;
            choosen_inline_result.emplace(
                cppgram::choosenInlineResult( jsonUpdate["choosen_inline_result"] ) );
        }
    }

    ~update(){};

    update(){};

    const update &operator=( const update &u )
    {
        if ( &u != this )
        {
            type = u.type;

            message = u.message;

            callback_query = u.callback_query;

            edited_message = u.edited_message;

            choosen_inline_result = u.choosen_inline_result;

            inline_query = u.inline_query;
        }

        return *this;
    };

    update &operator=( update &u )
    {
        if ( &u != this )
        {
            type = u.type;

            message = u.message;

            callback_query = u.callback_query;

            edited_message = u.edited_message;

            choosen_inline_result = u.choosen_inline_result;

            inline_query = u.inline_query;
        }

        return *this;
    };
};
}

#endif // CPPGRAM_UPDATE_H
