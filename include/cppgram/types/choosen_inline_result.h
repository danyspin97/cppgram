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

struct choosenInlineResult
{
    /** @} */
    std::string result_id;
    struct user *from;
    struct location *location;
    uid_32 inline_message_id;
    std::string query;

    choosenInlineResult(Json::Value &choosenInlineResult) : result_id(choosenInlineResult["result_id"].asString()),
                                                            from(new struct user(choosenInlineResult["from"])),
                                                            inline_message_id(choosenInlineResult["inline_message_id"].asUInt()),
                                                            query(choosenInlineResult["query"].asString())
    {}

    ~choosenInlineResult()
    {
        delete from;

        if (location != NULL)
            delete location;
    }

    choosenInlineResult()
    {}

    choosenInlineResult(const choosenInlineResult &prev)
    {
        *from = *(prev.from);
        *location = *(prev.location);

        result_id = prev.result_id;
        inline_message_id = prev.inline_message_id;
        query = prev.query;
    }
};

}

#endif //CPPGRAM_CHOOSEN_INLINE_RESULT_H
