#ifndef CPPGRAM_CHOOSEN_INLINE_RESULT_HPP
#define CPPGRAM_CHOOSEN_INLINE_RESULT_HPP

#include <string>

#include <json/json.h>

#include "location.hpp"
#include "user.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief A inline query choosed by the user
 * \details Represents a result of an inline query that was chosen by the user and sent to their
 * chat partner. [Api reference](https://core.telegram.org/bots/api#choseninlineresult) */
class ChosenInlineResult
{
    /** @} */

    public:
    /** \brief The unique identifier for the result that was chosen */
    std::string result_id;

    /** \brief The user that chose the result */
    User from;

    /** \brief <i>Optional</i>. Sender location, only for bots that require user location */
    std::experimental::optional<Location> location;

    /** \brief <i>Optional</i>. Identifier of the sent inline message.
     * \details Available only if there is an inline keyboard attached to the message. Will be also
     * received in callback queries and can be used to edit the message. */
    std::experimental::optional<std::string> inline_message_id;

    /** \brief The query that was used to obtain the result */
    std::string query;

    ChosenInlineResult( Json::Value &json_chosen_inline_result )
        : result_id( json_chosen_inline_result["result_id"].asString() )
        , from( json_chosen_inline_result["from"] )
        , query( json_chosen_inline_result["query"].asString() )
    {
        if ( !json_chosen_inline_result["location"].isNull() )
        {
            location.emplace( Location( json_chosen_inline_result["location"] ) );
        }

        if ( !json_chosen_inline_result["inline_message_id"].isNull() )
        {
            inline_message_id.emplace( json_chosen_inline_result["inline_message_id"].asString() );
        }
    }
};
}
}

#endif
