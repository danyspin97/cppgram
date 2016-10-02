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
#include "venue.h"
#include "video.h"
#include "voice.h"
#include "location.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A message send by user.
 * \details This object represents a message. (https://core.telegram.org/bots/api#message) */
struct message
{
    /** @} */

    /** \brief Unique message identifier */
    uid_32 message_id;

    /** \brief <i>Optional</i>. Sender, can be empty for messages sent to channels */
    struct user *from;

    /** \brief Date the message was sent in Unix time */
    date_unix date;

    /** \brief Conversation the message belongs to */
    struct chat *chat;

    /** \brief <i>Optional</i>. For forwarded messages, sender of the original message */
    struct user *forward_from;

    /** \brief <i>Optional</i>. For messages forwarded from a channel, information about the original channel */
    struct chat *forward_from_chat;

    /** \brief <i>Optional</i>. For forwarded messages, date the original message was sent in Unix time */
    date_unix forward_date;

    /** \brief <i>Optional</i>. For replies, the original message. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply. */
    struct message *reply_to_message;

    /** \brief <i>Optional</i>. Date the message was last edited in Unix time */
    date_unix edit_date;

    /** \brief <i>Optional</i>. For text messages, the actual UTF-8 text of the message, 0-4096 characters. */
    std::string text;

    /** \brief Optional. For text messages, an array of messageEntinty */
    std::vector<messageEntity *> entities;

    union
    {

        /** \brief <i>Optional</i>. Message is an audio file, information about the file */
        struct audio *audio;

        /** \brief <i>Optional</i>. Message is a general file, information about the file */
        struct document *document;

        /** \brief <i>Optional</i>. Message is a photo, available sizes of the photo */
        std::vector<struct photoSize *> photo;

        /** \brief<i>Optional</i>. Message is a sticker, information about the sticker */
        struct sticker *sticker;

        /** \brief <i>Optional</i>. Message is a video, information about the video */
        struct video *video;

        /** \brief <i>Optional</i>. Message is a voice message, information about the file */
        struct voice *voice;

        /** \brief <i>Optional</i>. Message is a shared contact, information about the contact */
        struct contact *contact;

        /** \brief <i>Optional</i>. Message is a shared location, information about the location */
        struct location *location;

        /** \brief <i>Optional</i>. Message is a venue, information about the venue */
        struct venue* venue;
    };

    /** \brief <i>Optional</i>. Caption for the document, photo or video, 0-200 characters */
    std::string caption;

    message(Json::Value &message) : message_id(message["message_id"].asUInt()),
                                    date(message["date"].asUInt()),
                                    chat(new struct chat(message["chat"])),
                                    forward_from(nullptr),
                                    forward_from_chat(nullptr),
                                    reply_to_message(nullptr)
    {
        if (!message["from"].isNull())
            from = new struct user(message["from"]);

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

        if (!message["audio"].isNull())
            audio = new struct audio(message["audio"]);
        else if (!message["document"].isNull())
            document = new struct document(message["document"]);
        else if (!message["photo"].isNull())
            for (Json::Value &photo_json : message["photo"])
                photo.push_back(new struct photoSize(photo_json));
        else if (!message["sticker"].isNull())
            sticker = new struct sticker(message["sticker"]);
        else if (!message["video"].isNull())
            video = new struct video(message["video"]);
        else if (!message["voice"].isNull())
            voice = new struct voice(message["voice"]);
        else if (!message["contact"].isNull())
            contact = new struct contact(message["contact"]);
        else if (!message["location"].isNull())
            location = new struct location(message["location"]);
        else if (!message["venue"].isNull())
            venue = new struct venue(message["venue"]);

        if (!message["caption"].isNull())
            caption = message["caption"].asString();
    }

    message()
    {};

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

        if (entities.size() != 0)
        {
            unsigned short entities_size = entities.size();
            for (int i = 0; i != entities_size; i++)
                delete entities[i];
        }

        if (audio != NULL)
            delete audio;
        else if (document != NULL)
            delete document;
        else if (photo.size() != 0)
        {
            unsigned short photo_size = photo.size();
            for (int i = 0; i != photo_size; i++)
                delete photo[i];
        }
        else if (sticker != NULL)
            delete sticker;
        else if (video != NULL)
            delete video;
        else if (voice != NULL)
            delete voice;
        else if (contact != NULL)
            delete contact;
        else if (location != NULL)
            delete location;
        else if (venue != NULL)
            delete venue;
    }

    message(const message &prev)
    {
        chat = prev.chat;
        from = prev.from;
        if (prev.forward_from != NULL)
        {
            forward_from = prev.forward_from;
            forward_from_chat = prev.forward_from_chat;
        }

        if (prev.reply_to_message != NULL)
            reply_to_message = prev.reply_to_message;

        date = prev.date;
        text = prev.text;
        edit_date = prev.edit_date;
        message_id = prev.message_id;

        if (prev.audio != NULL)
             audio = prev.audio;
        else if (prev.document != NULL)
            document = prev.document;
        else if (prev.photo.size() != 0)
            photo = prev.photo;
        else if (prev.sticker != NULL)
            sticker = prev.sticker;
        else if (prev.video != NULL)
            video = prev.video;
        else if (prev.voice != NULL)
            voice = prev.voice;
        else if (prev.contact != NULL)
            contact = prev.contact;
        else if (prev.location != NULL)
            location = prev.location;
        else if (prev.venue != NULL)
            venue = prev.venue;
    }
};

}

#endif //CPPGRAM_MESSAGE_H
