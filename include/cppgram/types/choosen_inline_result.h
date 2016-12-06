#ifndef CPPGRAM_CHOOSEN_INLINE_RESULT_H
#define CPPGRAM_CHOOSEN_INLINE_RESULT_H

#include <string>

#include <json/json.h>

#include "user.h"
#include "location.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A inline query choosed by the user
 * \details Represents a result of an inline query that was chosen by the user and sent to their chat partner. [Api reference](https://core.telegram.org/bots/api#choseninlineresult) */
struct choosenInlineResult
{
    /** @} */

    /** \brief The unique identifier for the result that was chosen */
    std::string result_id;

    /** \brief The user that chose the result */
    struct user from;

    /** \brief <i>Optional</i>. Sender location, only for bots that require user location */
    std::experimental::optional<cppgram::location> location;

    /** \brief <i>Optional</i>. Identifier of the sent inline message.
     * \details Available only if there is an inline keyboard attached to the message. Will be also received in callback queries and can be used to edit the message. */
    std::experimental::optional<int_fast32_t> inline_message_id;

    /** \brief The query that was used to obtain the result */
    std::string query;

    choosenInlineResult(Json::Value &jsonChoosenInlineResult) : result_id(jsonChoosenInlineResult["result_id"].asString()),
                                                            from(jsonChoosenInlineResult["from"]),
                                                            query(jsonChoosenInlineResult["query"].asString())
    {

        if (!jsonChoosenInlineResult["location"].isNull())
        {
            location.emplace(cppgram::location(jsonChoosenInlineResult["location"]));
        }

        inline_message_id.emplace(jsonChoosenInlineResult["inline_message_id"].asUInt());

    }

    choosenInlineResult()
    {}

};

}

#endif //CPPGRAM_CHOOSEN_INLINE_RESULT_H
