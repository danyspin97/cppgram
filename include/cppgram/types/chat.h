#ifndef CPPGRAM_CHAT_H
#define CPPGRAM_CHAT_H

#include <string>
#include <cstring>

#include <json/json.h>

#include "enums.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Chat object.
 * \details This object represents a chat. (https://core.telegram.org/bots/api#user) */
struct chat
{
    /** @} */

    /** \brief Unique identifier for this chat. */
    int_fast64_t id;

    /** \brief Type of chat */
    ChatType type;

    /** \brief <i>Optional</i>. Title, for supergroups, channels and group chats */
    std::string title,

    /** \brief <i>Optional</i>. Username, for private chats, supergroups and channels if available */
            username,
    /** \brief <i>Optional</i>. First name of the other party in a private chat */
            first_name,
    /** \brief <i>Optional</i>. Last name of the other party in a private chat */
            last_name;

    chat(Json::Value &jsonChat) : id(jsonChat["id"].asInt64())
    {
        title = !jsonChat["title"].isNull() ? jsonChat["title"].asString() : "";

        username = !jsonChat["username"].isNull() ? jsonChat["username"].asString() : "";

        first_name = !jsonChat["first_name"] ? jsonChat["first_name"].asString() : "";

        last_name = !jsonChat["last_name"] ? jsonChat["last_name"].asString() : "";

        if (!jsonChat["type"].isNull())
        {
            std::vector<std::string> type_strings = {"private", "group", "supergroup", "channel"};
            int i = 3; // type_strings.size() - 1
            std::string chat_type = jsonChat["type"].asString();
            while (i > 0 && chat_type.compare(type_strings[i]) != 0)
            {
                i--;
            }

            type = static_cast<ChatType>(i);
        }
    }

    chat()
    {}

    ~chat()
    {}
};

}

#endif //CPPGRAM_CHAT_H
