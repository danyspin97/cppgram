#ifndef CPPGRAM_INLINE_QUERY_H
#define CPPGRAM_INLINE_QUERY_H

#include <string>

#include <json/json.h>

#include "user.h"
#include "location.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Incoming inline query.
 * \details This object represents an incoming inline query. (https://core.telegram.org/bots/api#inlinequery) */
struct inlineQuery
{
    /** @} */

    /** \brief Unique identifier for this query */
    std::string id;

    /** \brief Sender */
    struct user *from;

    /** \brief <i>Optional</i>. Sender location, only for bots that request user location */
    struct location *location;

    /** \brief Text of the query, up to 512 characters. */
    std::string query,

    /** \brief Offset of the results to be returned, can be controlled by the bot */
            offset;

    inlineQuery(Json::Value &jsonInlineQuery)
            : id(jsonInlineQuery["id"].asString()),
              from(new struct user(jsonInlineQuery["from"])),
              query(jsonInlineQuery["query"].asString()),
              offset(jsonInlineQuery["offset"].asString())

    {
        location = !jsonInlineQuery["location"].isNull() ? new struct location(jsonInlineQuery["location"]) : nullptr;
    }

    inlineQuery()
    {}

    ~inlineQuery()
    {
        delete from;

        if (location != NULL)
        {
            delete location;
        }
    }

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
