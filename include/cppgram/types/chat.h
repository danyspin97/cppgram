#ifndef CPPGRAM_CHAT_H
#define CPPGRAM_CHAT_H

#include <string>
#include <json/json.h>
#include "integers.h"
#include "enums.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** This object represents a chat. (https://core.telegram.org/bots/api#user) */
struct chat
{
    /** @} */

    /** Unique identifier for this chat. */
    id_64 id;
    /** Type of chat */
    ChatType type;
    /** <i>Optional</i>. Title, for supergroups, channels and group chats */
    std::string title,
    /** <i>Optional</i>. Username, for private chats, supergroups and channels if available */
            username,
    /** <i>Optional</i>. First name of the other party in a private chat */
            first_name,
    /** <i>Optional</i>. Last name of the other party in a private chat */
            last_name;
    chat(Json::Value &chat) : id(chat["id"].asInt64())
    {
        std::string typechat = chat["type"].asString();
        if (typechat == "private")
            type = ChatType::Private;
        else if (typechat == "group")
            type = ChatType::Group;
        else if (typechat == "supergroup")
            type = ChatType::Supergroup;
        else if (typechat == "channel")
            type = ChatType::Channel;

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
