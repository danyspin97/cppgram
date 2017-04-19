#ifndef CPPGRAM_MESSAGEENTITY_HPP
#define CPPGRAM_MESSAGEENTITY_HPP

#include <cstring>
#include <experimental/optional>
#include <string>

#include <json/json.h>

#include "enums.hpp"
#include "user.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief Entity in the message
 * \details This object represents one special entity in a text message. For example, hashtags,
 * usernames, URLs, etc. (https://core.telegram.org/bots/api#messageentity) */
class MessageEntity
{
    /** @} */

    public:
    /** \brief Type of the entity. */
    EMessageEntity type;

    /** \brief Offset in UTF-16 code units to the start of the entity */
    int offset,
            /** \brief Length of the entity in UTF-16 code units */
            length;

    /** \brief <i>Optional</i>. For “text_link” only, url that will be opened after user taps on the
     * text */
    std::experimental::optional<std::string> url;

    /** \brief <i>Optional</i>. For “text_mention” only, the mentioned user */
    std::experimental::optional<User> user;

    MessageEntity( Json::Value &json_message_entity )
        : offset( json_message_entity["offset"].asInt() )
        , length( json_message_entity["length"].asInt() )
    {
        std::vector<std::string> entity_strings = {"mention",
                                                   "hashtag",
                                                   "bot_command",
                                                   "url",
                                                   "email",
                                                   "bold",
                                                   "italic",
                                                   "code",
                                                   "pre",
                                                   "text_link",
                                                   "text_mention"};
        int i = 10; // entity_strings.size() - 1

        std::string entity_type = json_message_entity["type"].asString();
        while ( i > 0 && entity_type.compare( entity_strings[i] ) != 0 )
        {
            i--;
        }

        type = static_cast<EMessageEntity>( i );

        if ( !json_message_entity["url"].isNull() )
        {
            url.emplace( json_message_entity["url"].asString() );
        }

        if ( !json_message_entity["user"].isNull() )
        {
            user.emplace( User( json_message_entity["user"] ) );
        }
    }

    MessageEntity( const MessageEntity &prev )
    {
        user = prev.user;

        type = prev.type;

        url    = prev.url;
        offset = prev.offset;
        length = prev.length;
    }
};
}
}

#endif
