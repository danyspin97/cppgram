#ifndef CPPGRAM_INLINE_QUERY_HPP
#define CPPGRAM_INLINE_QUERY_HPP

#include <string>

#include <json/json.h>

#include "location.hpp"
#include "user.hpp"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief Incoming inline query.
 * \details This object represents an incoming inline query.
 * (https://core.telegram.org/bots/api#inlinequery) */
class InlineQuery
{
    /** @} */

    public:
    /** \brief Unique identifier for this query */
    std::string id;

    /** \brief Sender */
    User from;

    /** \brief <i>Optional</i>. Sender location, only for bots that request user location */
    std::experimental::optional<Location> location;

    /** \brief Text of the query, up to 512 characters. */
    std::string query,

            /** \brief Offset of the results to be returned, can be controlled by the bot */
            offset;

    InlineQuery( Json::Value &json_inline_query )
        : id( json_inline_query["id"].asString() )
        , from( User( json_inline_query["from"] ) )
        , query( json_inline_query["query"].asString() )
        , offset( json_inline_query["offset"].asString() )

    {
        if ( !json_inline_query["localtion"].isNull() )
        {
            location.emplace( Location( json_inline_query["location"] ) );
        }
    }
};
}

#endif
