#ifndef CPPGRAM_UPDATE_HPP
#define CPPGRAM_UPDATE_HPP

#include <string>

#include <json/json.h>

#include "callback_query.hpp"
#include "chosen_inline_result.hpp"
#include "inline_query.hpp"
#include "message.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

class Update
{
    /** @} */

    public:
    EUpdate type;
    uint_fast32_t   update_id;

    std::experimental::optional<Message>            message;
    std::experimental::optional<Message>            edited_message;
    std::experimental::optional<InlineQuery>        inline_query;
    std::experimental::optional<ChosenInlineResult> chosen_inline_result;
    std::experimental::optional<CallbackQuery>      callback_query;

    Update( Json::Value &json_update )
        : update_id( json_update["update_id"].asUInt() )
    {
        if ( !json_update["message"].isNull() )
        {
            type = EUpdate::eMessage;
            message.emplace( Message( json_update["message"] ) );
        }
        else if ( !json_update["callback_query"].isNull() )
        {
            type = EUpdate::eCallbackQuery;
            callback_query.emplace( CallbackQuery( json_update["callback_query"] ) );
        }
        else if ( !json_update["edited_message"].isNull() )
        {
            type = EUpdate::eEditedMessage;
            edited_message.emplace( Message( json_update["edited_message"] ) );
        }
        else if ( !json_update["inline_query"].isNull() )
        {
            type = EUpdate::eInlineQuery;
            inline_query.emplace( InlineQuery( json_update["inline_query"] ) );
        }
        else if ( !json_update["chosen_inline_result"].isNull() )
        {
            type = EUpdate::eChosenInlineResult;
            chosen_inline_result.emplace(
                    ChosenInlineResult( json_update["chosen_inline_result"] ) );
        }
    }

    ~Update(){};

    Update(){};

    const Update &operator=( const Update &u )
    {
        if ( &u != this )
        {
            update_id            = u.update_id;
            type                 = u.type;
            message              = u.message;
            callback_query       = u.callback_query;
            edited_message       = u.edited_message;
            chosen_inline_result = u.chosen_inline_result;
            inline_query         = u.inline_query;
        }

        return *this;
    };

    Update &operator=( Update &u )
    {
        if ( &u != this )
        {
            update_id            = u.update_id;
            type                 = u.type;
            message              = u.message;
            callback_query       = u.callback_query;
            edited_message       = u.edited_message;
            chosen_inline_result = u.chosen_inline_result;
            inline_query         = u.inline_query;
        }

        return *this;
    };
};
}
}

#endif
