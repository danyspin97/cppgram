#ifndef CPPGRAM_INLINE_QUERY_H
#define CPPGRAM_INLINE_QUERY_H

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

/** This object represents an incoming inline query. (https://core.telegram.org/bots/api#inlinequery) */
struct inlineQuery
{
    /** @} */

    /** Unique identifier for this query */
    std::string id;

    /** Sender */
    struct user *from;

    /** <i>Optional</i>. Sender location, only for bots that request user location */
    struct location *location;

    /** Text of the query (up to 512 characters) */
    std::string query,

    /** Offset of the results to be returned, can be controlled by the bot */
            offset;

    inlineQuery(Json::Value &inlineQuery)
            : id(inlineQuery["id"].asString()), query(inlineQuery["query"].asString()),
              offset(inlineQuery["offset"].asString()), from(new struct user(inlineQuery["from"])),
              location(nullptr)
    {
        if (!inlineQuery["location"].isNull())
        {
            location = new struct location(inlineQuery["location"]);
        }
    }

    ~inlineQuery()
    {
        delete from;

        if (location != NULL)
            delete location;
    }

    inlineQuery()
    {}

    inlineQuery(const inlineQuery &prev)
    {
        *from = *(prev.from);
        *location = *(prev.location);

        id = prev.id;
        query = prev.query;
        offset = prev.offset;
    }
};

}

#endif //CPPGRAM_INLINE_QUERY_H
