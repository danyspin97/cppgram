#ifndef CPPGRAM_MESSAGE_H
#define CPPGRAM_MESSAGE_H

#include <string>

#include <json/json.h>

#include "integers.h"
#include "chat.h"
#include "user.h"
#include "audio.h"
#include "contact.h"
#include "document.h"
#include "message_entity.h"
#include "message_entity.h"
#include "sticker.h"
#include "video.h"
#include "voice.h"
#include "location.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** This object represents a message. (https://core.telegram.org/bots/api#message) */
struct message
{
    /** @} */

    /** Unique message identifier */
    uid_32 message_id;

    /** <i>Optional</i>. Sender, can be empty for messages sent to channels */
    struct user *from;

    /** Date the message was sent in Unix time */
    date_unix date;

    /** Conversation the message belongs to */
    struct chat *chat;

    /** <i>Optional</i>. For forwarded messages, sender of the original message */
    struct user *forward_from;

    /** <i>Optional</i>. For messages forwarded from a channel, information about the original channel */
    struct chat *forward_from_chat;

    /** <i>Optional</i>. For forwarded messages, date the original message was sent in Unix time */
    date_unix forward_date;

    /** <i>Optional</i>. For replies, the original message. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply. */
    struct message *reply_to_message;

    /** <i>Optional</i>. Date the message was last edited in Unix time */
    date_unix edit_date;

    /** <i>Optional</i>. For text messages, the actual UTF-8 text of the message, 0-4096 characters. */
    std::string text;

    /** Optional. For text messages, special entities like usernames, URLs, bot commands, etc. that appear in the text */
    std::vector<messageEntity *> entities;

    union
    {

        /** <i>Optional</i>. Message is an audio file, information about the file */
        struct audio audio;

        /** <i>Optional</i>. Message is a general file, information about the file */
        struct document document;

        /** <i>Optional</i>. Message is a photo, available sizes of the photo */
        std::vector<struct photoSize> photo;

        /** <i>Optional</i>. Message is a sticker, information about the sticker */
        struct sticker sticker;

        /** <i>Optional</i>. Message is a video, information about the video */
        struct video video;

        /** <i>Optional</i>. Message is a voice message, information about the file */
        struct voice voice;

        /** <i>Optional</i>. Message is a shared contact, information about the contact */
        struct contact contact;

        /** <i>Optional</i>. Message is a shared location, information about the location */
        struct location location;

        /** <i>Optional</i>. Message is a venue, information about the venue */
        //struct venue venue;
    };

    /** <i>Optional</i>. Caption for the document, photo or video, 0-200 characters */
    std::string caption;

    message(Json::Value &message) : message_id(message["message_id"].asUInt()),
                                    from(new struct user(message["from"])),
                                    date(message["date"].asUInt()),
                                    chat(new struct chat(message["chat"])),
                                    forward_from(nullptr),
                                    forward_from_chat(nullptr),
                                    reply_to_message(nullptr)
    {
        if (!message["forward_from"].isNull())
        {
            forward_from = new struct user(message["forward_from"]);
            forward_from_chat = new struct chat(message["forward_from_chat"]);
            forward_date = message["forward_date"].asUInt();
        }

        if (!message["reply_to_message"].isNull())
            reply_to_message = new struct message(message["reply_to_message"]);

        if (!message["edit_date"].isNull())
            edit_date = message["edit_date"].asUInt();

        if (!message["text"].isNull())
        {
            text = message["text"].asString();
        }

        if (!message["entities"].isNull())
        {
            for (Json::Value &entity: message["entities"])
            {
                entities.push_back(new struct messageEntity(entity));
            }
        }
    }

    message(const message &prev)
    {
        *chat = *(prev.chat);
        *from = *(prev.from);
        *forward_from = *(prev.forward_from);
        *forward_from_chat = *(prev.forward_from_chat);
        //*reply_to_message = *(prev.reply_to_message);

        date = prev.date;
        text = prev.text;
        edit_date = prev.edit_date;
        message_id = prev.message_id;
    }

    ~message()
    {
        delete from;
        delete chat;

        if (forward_from != NULL)
            delete forward_from;
        if (forward_from_chat != NULL)
            delete forward_from_chat;
        if (reply_to_message != NULL)
            delete reply_to_message;
    }

    message();
};

}

#endif //CPPGRAM_MESSAGE_H
