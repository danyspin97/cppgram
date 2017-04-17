#ifndef CPPGRAM_CHAT_HPP
#define CPPGRAM_CHAT_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

#include "enums.hpp"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief Chat object.
 * \details This object represents a chat. (https://core.telegram.org/bots/api#user) */
class Chat
{
    /** @} */

    public:
    /** \brief Unique identifier for this chat. */
    int_fast64_t id;

    /** \brief Type of chat */
    ChatType type;

    /** \brief <i>Optional</i>. Title, for supergroups, channels and group chats */
    std::experimental::optional<std::string> title,

            /** \brief <i>Optional</i>. Username, for private chats, supergroups and channels if
               available */
            username,
            /** \brief <i>Optional</i>. First name of the other party in a private chat */
            first_name,
            /** \brief <i>Optional</i>. Last name of the other party in a private chat */
            last_name;

    Chat( Json::Value &json_chat )
        : id( json_chat["id"].asInt64() )
    {
        if ( !json_chat["title"].isNull() )
        {
            title.emplace( json_chat["title"].asString() );
        }

        if ( !json_chat["username"].isNull() )
        {
            username.emplace( json_chat["username"].asString() );
        }

        if ( !json_chat["first_name"].isNull() )
        {
            first_name.emplace( json_chat["first_name"].asString() );
        }

        if ( !json_chat["last_name"].isNull() )
        {
            last_name.emplace( json_chat["last_name"].asString() );
        }

        if ( !json_chat["type"].isNull() )
        {
            std::vector<std::string> type_strings = {"private", "group", "supergroup", "channel"};
            int                      i            = 3; // type_strings.size() - 1
            std::string              chat_type    = json_chat["type"].asString();
            while ( i > 0 && chat_type.compare( type_strings[i] ) != 0 )
            {
                i--;
            }

            type = static_cast<ChatType>( i );
        }
        else
        {
            type = ChatType::Private;
        }
    }

    Chat() {}
};
}

#endif
