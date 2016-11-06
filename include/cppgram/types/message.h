#ifndef CPPGRAM_MESSAGE_H
#define CPPGRAM_MESSAGE_H

#include <string>

#include <json/json.h>

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
    int_fast32_t message_id;

    /** \brief <i>Optional</i>. Sender, can be empty for messages sent to channels */
    std::experimental::optional<user> from;

    /** \brief Date the message was sent in Unix time */
    int_fast32_t date;

    /** \brief Conversation the message belongs to */
    cppgram::chat chat;

    /** \brief <i>Optional</i>. For forwarded messages, sender of the original message */
    std::experimental::optional<user> forward_from;

    /** \brief <i>Optional</i>. For messages forwarded from a channel, information about the original channel */
    std::experimental::optional<cppgram::chat> forward_from_chat;

    /** \brief <i>Optional</i>. For forwarded messages, date the original message was sent in Unix time */
    std::experimental::optional<int_fast32_t> forward_date;

    /** \brief <i>Optional</i>. For replies, the original message. Note that the Message object in this field will not contain further reply_to_message fields even if it itself is a reply. */
    cppgram::message *reply_to_message;

    /** \brief <i>Optional</i>. Date the message was last edited in Unix time */
    std::experimental::optional<int_fast32_t> edit_date;

    /** \brief <i>Optional</i>. For text messages, the actual UTF-8 text of the message, 0-4096 characters. */
    std::experimental::optional<std::string> text;

    /** \brief <i>Optional</i>. For text messages, an array of messageEntinty */
    std::vector<messageEntity> entities;

    union
    {
        /** \brief <i>Optional</i>. Message is an audio file, information about the file */
        std::experimental::optional<cppgram::audio> audio;

        /** \brief <i>Optional</i>. Message is a general file, information about the file */
        std::experimental::optional<cppgram::document> document;

        /** \brief <i>Optional</i>. Message is a photo, available sizes of the photo */
        std::vector<photoSize> photo;

        /** \brief<i>Optional</i>. Message is a sticker, information about the sticker */
        std::experimental::optional<cppgram::sticker> sticker;

        /** \brief <i>Optional</i>. Message is a video, information about the video */
        std::experimental::optional<cppgram::video> video;

        /** \brief <i>Optional</i>. Message is a voice message, information about the file */
        std::experimental::optional<cppgram::voice> voice;

        /** \brief <i>Optional</i>. Message is a shared contact, information about the contact */
        std::experimental::optional<cppgram::contact> contact;

        /** \brief <i>Optional</i>. Message is a shared location, information about the location */
        std::experimental::optional<cppgram::location> location;

        /** \brief <i>Optional</i>. Message is a venue, information about the venue */
        std::experimental::optional<cppgram::venue> venue;
    };

    /** \brief <i>Optional</i>. Caption for the document, photo or video, 0-200 characters */
    std::experimental::optional<std::string> caption;

    message(Json::Value &jsonMessage) : message_id(jsonMessage["message_id"].asUInt()),
                                    date(jsonMessage["date"].asUInt()),
                                    chat(jsonMessage["chat"])
    {

        if (!jsonMessage["from"].isNull())
        {

            from.emplace(user(jsonMessage["from"]));

        }

        if (!jsonMessage["forward_from"].isNull())
        {
            forward_from.emplace(user(jsonMessage["forward_from"]));
            forward_from_chat.emplace(cppgram::chat(jsonMessage["forward_from_chat"]));
            forward_date.emplace(jsonMessage["forward_date"].asUInt());
        }

        if (!jsonMessage["reply_to_message"].isNull())
        {

            //reply_to_message.emplace(cppgram::message(jsonMessage["reply_to_jsonMessage"]));

        }

        /*edit_date.emplace() = !jsonMessage["edit_date"].isNull() ? jsonMessage["edit_date"].asUInt() : int_fast32_t();

        text.emplace(jsonMessage["text"].asString());

        if (!jsonMessage["entities"].isNull())
        {
            for (Json::Value &entity: jsonMessage["entities"])
            {
                entities.push_back(new struct messageEntity(entity));
            }
        }

        if (!jsonMessage["audio"].isNull())
        {
            audio = new struct audio(jsonMessage["audio"]);
        }
        else if(!jsonMessage["document"].isNull())
        {
            document = new struct document(jsonMessage["document"]);
        }
        else if (!jsonMessage["photo"].isNull())
        {
            for (Json::Value &photo_json : jsonMessage["photo"])
            {
                photo.push_back(new struct photoSize(photo_json));
            }
        }
        else if (!jsonMessage["sticker"].isNull())
        {
            sticker = new struct sticker(jsonMessage["sticker"]);
        }
        else if (!jsonMessage["video"].isNull())
        {
            video = new struct video(jsonMessage["video"]);
        }
        else if (!jsonMessage["voice"].isNull())
        {
            voice = new struct voice(jsonMessage["voice"]);
        }
        else if (!jsonMessage["contact"].isNull())
        {
            contact = new struct contact(jsonMessage["contact"]);
        }
        else if (!jsonMessage["location"].isNull())
        {
            location = new struct location(jsonMessage["location"]);
        }
        else if (!jsonMessage["venue"].isNull())
        {
            venue = new struct venue(jsonMessage["venue"]);
        }
        if (!jsonMessage["caption"].isNull())
        {
            caption = jsonMessage["caption"].asString();
        } */
    }

    message()
    {};

    ~message()
    {};

};

}

#endif //CPPGRAM_MESSAGE_H
