#ifndef CPPGRAM_CHAT_H
#define CPPGRAM_CHAT_H

#include <string>
#include <cstring>

#include <json/json.h>

#include "integers.h"
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
    id_64 id;

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

    chat(Json::Value &chat) : id(chat["id"].asInt64())
    {
        const char *mystr[] = {"private", "group", "supergroup", "channel"};

        int i = 3;

        const char *chat_type = chat["type"].asCString();
        while (i > 0 && strcmp(mystr[i], chat_type) != 0)
            i--;

        type = static_cast<ChatType>(i);

        if (!chat["title"].isNull())
            title = chat["title"].asString();

        if (!chat["username"].isNull())
            username = chat["username"].asString();

        if (!chat["first_name"])
            first_name = chat["first_name"].asString();

        if (!chat["last_name"])
            last_name = chat["last_name"].asString();
    }

    chat()
    {}

    ~chat()
    {}
};

}

#endif //CPPGRAM_CHAT_H
