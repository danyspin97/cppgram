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

/** \brief Entity in the message
 * \details This object represents one special entity in a text message. For example, hashtags, usernames, URLs, etc. (https://core.telegram.org/bots/api#messageentity) */
struct messageEntity
{
    /** @} */

    /** \brief Type of the entity. */
    MessageEntityType type;

    /** \brief Offset in UTF-16 code units to the start of the entity */
    int offset,
    /** \brief Length of the entity in UTF-16 code units */
            lenght;

    /** \brief <i>Optional</i>. For “text_link” only, url that will be opened after user taps on the text */
    std::string url;

    /** \brief <i>Optional</i>. For “text_mention” only, the mentioned user */
    struct user *from;

    messageEntity(Json::Value &jsonMessageEntity)
            : offset(jsonMessageEntity["offset"].asInt()), lenght(jsonMessageEntity["length"].asInt())
    {
        std::vector<std::string> entity_strings = {"mention", "hashtag", "bot_command", "url", "email", "bold", "italic", "code", "pre", "text_link", "text_mention"};
        int i = 10; // entity_strings.size() - 1
        std::string entity_type = jsonMessageEntity["type"].asString();
        while (i > 0 && entity_type.compare(entity_strings[i]) != 0)
        {
            i--;
        }

        type = static_cast<MessageEntityType>(i);

        url = !jsonMessageEntity["url"].isNull() ? jsonMessageEntity["url"].asString() : "";

        from = !jsonMessageEntity["user"].isNull() ? new user(jsonMessageEntity["user"]) : nullptr;

    }

    messageEntity(const messageEntity &prev)
    {

        from = prev.from;

        type = prev.type;

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
