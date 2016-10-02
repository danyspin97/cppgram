#ifndef CPPGRAM_MESSAGEENTITY_H
#define CPPGRAM_MESSAGEENTITY_H

#include <string>

#include <json/json.h>
#include <cstring>

#include "enums.h"
#include "user.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** This object represents one special entity in a text message. For example, hashtags, usernames, URLs, etc. (https://core.telegram.org/bots/api#messageentity) */
struct messageEntity
{
    /** @} */

    /** Type of the entity. */
    MessageEntityType type;

    /** Offset in UTF-16 code units to the start of the entity */
    int offset,
    /** Length of the entity in UTF-16 code units */
            lenght;

    /** <i>Optional</i>. For “text_link” only, url that will be opened after user taps on the text */
    std::string url;

    /** <i>Optional</i>. For “text_mention” only, the mentioned user */
    struct user *from;

    messageEntity(Json::Value &messageEntity)
            : offset(messageEntity["offset"].asInt()), lenght(messageEntity["length"].asInt())
    {
        /*std::string entity_type = messageEntity["type"].asString();
        if (strcmp(entity_type, "mention") == 0)
            type = MessageEntityType::mention;
        else if (strcmp(entity_type, "hashtag") == 0)
            type = MessageEntityType::hashtag;
        else if (strcmp(entity_type, "bot_command"))
            type = MessageEntityType::bot_command;
        else if (strcmp(entity_type, "url") == 0)
            type = MessageEntityType::url;
        else if (strcmp(entity_type, "email") == 0)
            type = MessageEntityType::email;
        else if (strcmp(entity_type, "bold") == 0)
            type = MessageEntityType::bold;
        else if (strcmp(entity_type, "italic") == 0)
            type = MessageEntityType::italic;
        else if (strcmp(entity_type, "code") == 0)
            type = MessageEntityType::code;
        else if (strcmp(entity_type, "pre") == 0)
            type = MessageEntityType::pre;
        else if (strcmp(entity_type, "text_link") == 0)
            type = MessageEntityType::text_link;
        else if (strcmp(entity_type, "text_mention") == 0)
            type = MessageEntityType::text_mention;*/

        if (!messageEntity["url"].isNull())
            url = messageEntity["url"].asString();

        if (!messageEntity["user"].isNull())
            from = new user(messageEntity["user"]);

    }

    messageEntity(const messageEntity &prev)
    {

        *from = *(prev.from);

        url = prev.url;
        offset = prev.offset;
        lenght = prev.lenght;

    }

    ~messageEntity()
    { if (from != NULL) delete from; }
    messageEntity()
    {};
};

}

#endif //CPPGRAM_MESSAGEENTITY_H
