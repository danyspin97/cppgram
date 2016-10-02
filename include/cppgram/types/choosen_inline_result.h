#ifndef CPPGRAM_CHOOSEN_INLINE_RESULT_H
#define CPPGRAM_CHOOSEN_INLINE_RESULT_H

#include <string>

#include <json/json.h>

#include "integers.h"
#include "user.h"
#include "location.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A inline query choosed by the user
 * \details Represents a result of an inline query that was chosen by the user and sent to their chat partner. (https://core.telegram.org/bots/api#choseninlineresult) */
struct choosenInlineResult
{
    /** @} */

    /** \brief The unique identifier for the result that was chosen */
    std::string result_id;

    /** \brief The user that chose the result */
    struct user *from;

    /** \brief <i>Optional</i>. Sender location, only for bots that require user location */
    struct location *location;

    /** \brief <i>Optional</i>. Identifier of the sent inline message.
     * \details Available only if there is an inline keyboard attached to the message. Will be also received in callback queries and can be used to edit the message. */
    uid_32 inline_message_id;

    /** \brief The query that was used to obtain the result */
    std::string query;

    choosenInlineResult(Json::Value &choosenInlineResult) : result_id(choosenInlineResult["result_id"].asString()),
                                                            from(new struct user(choosenInlineResult["from"])),
                                                            query(choosenInlineResult["query"].asString())
    {
        if (!choosenInlineResult["location"].isNull())
            location = new struct location(choosenInlineResult["location"]);

        if (!choosenInlineResult["inline_message_id"].isNull())
            inline_message_id = choosenInlineResult["inline_message_id"].asUInt();
    }

    choosenInlineResult()
    {}

    ~choosenInlineResult()
    {
        delete from;

        if (location != NULL)
            delete location;
    }

    choosenInlineResult(const choosenInlineResult &prev)
    {
        from = prev.from;
        location = prev.location;

        result_id = prev.result_id;
        inline_message_id = prev.inline_message_id;
        query = prev.query;
    }

};

}

#endif //CPPGRAM_CHOOSEN_INLINE_RESULT_H
