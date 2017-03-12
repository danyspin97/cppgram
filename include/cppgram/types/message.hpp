#ifndef CPPGRAM_MESSAGE_HPP
#define CPPGRAM_MESSAGE_HPP

#include <string>

#include <json/json.h>

#include "audio.h"
#include "chat.h"
#include "contact.h"
#include "document.h"
#include "location.h"
#include "message_entity.h"
#include "message_entity.h"
#include "sticker.h"
#include "user.h"
#include "venue.h"
#include "video.h"
#include "voice.h"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief A message send by user.
 * \details This object represents a message. (https://core.telegram.org/bots/api#message) */
class message
{
    /** @} */

    public:
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

    /** \brief <i>Optional</i>. For messages forwarded from a channel, information about the
     * original channel */
    std::experimental::optional<cppgram::chat> forward_from_chat;

    /** \brief <i>Optional</i>. For forwarded messages, date the original message was sent in Unix
     * time */
    std::experimental::optional<int_fast32_t> forward_date;

    /** \brief <i>Optional</i>. For replies, the original message. Note that the Message object in
     * this field will not contain further reply_to_message fields even if it itself is a reply. */
    cppgram::message *reply_to_message;

    /** \brief <i>Optional</i>. Date the message was last edited in Unix time */
    std::experimental::optional<int_fast32_t> edit_date;

    /** \brief <i>Optional</i>. For text messages, the actual UTF-8 text of the message, 0-4096
     * characters. */
    std::experimental::optional<std::string> text;

    /** \brief <i>Optional</i>. For text messages, an array of messageEntinty */
    std::vector<messageEntity> entities;

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

    /** \brief <i>Optional</i>. Caption for the document, photo or video, 0-200 characters */
    std::experimental::optional<std::string> caption;

    message( Json::Value &json_message )
        : message_id( jsonMessage["message_id"].asUInt() )
        , date( json_message["date"].asUInt() )
        , chat( json_message["chat"] )
    {
        if ( !json_message["from"].isNull() )
        {
            from.emplace( user( json_message["from"] ) );
        }

        if ( !json_message["forward_from"].isNull() )
        {
            forward_from.emplace( user( json_message["forward_from"] ) );
            forward_from_chat.emplace( cppgram::chat( json_message["forward_from_chat"] ) );
            forward_date.emplace( json_message["forward_date"].asUInt() );
        }

        if ( !json_message["reply_to_message"].isNull() )
        {
            reply_to_message = new cppgram::message( json_message["reply_to_message"] );
        }

        if ( !json_message["edit_date"].isNull() )
        {
            edit_date.emplace( json_message["edit_date"].asUInt() );
        }

        text.emplace( json_message["text"].asString() );

        /*if (!json_message["entities"].isNull())
        {
            for (Json::Value &entity: json_message["entities"])
            {
                entities.push_back(new struct messageEntity(entity));
            }
        } */

        if ( !json_message["audio"].isNull() )
        {
            audio.emplace( cppgram::audio( json_message["audio"] ) );
        }
        else if ( !json_message["document"].isNull() )
        {
            document.emplace( cppgram::document( json_message["document"] ) );
        }
        else if ( !json_message["photo"].isNull() )
        {
            for ( Json::Value &photo_json : json_message["photo"] )
            {
                photo.push_back( photoSize( photo_json ) );
            }
        }
        else if ( !json_message["sticker"].isNull() )
        {
            sticker.emplace( cppgram::sticker( json_message["sticker"] ) );
        }
        else if ( !json_message["video"].isNull() )
        {
            video.emplace( cppgram::video( json_message["video"] ) );
        }
        else if ( !json_message["voice"].isNull() )
        {
            voice.emplace( cppgram::voice( json_message["voice"] ) );
        }
        else if ( !json_message["contact"].isNull() )
        {
            contact.emplace( cppgram::contact( json_message["contact"] ) );
        }
        else if ( !json_message["location"].isNull() )
        {
            location.emplace( cppgram::location( json_message["location"] ) );
        }
        else if ( !json_message["venue"].isNull() )
        {
            venue.emplace( cppgram::venue( json_message["venue"] ) );
        }

        if ( !json_message["caption"].isNull() )
        {
            caption = json_message["caption"].asString();
        }
    }

    message(){};

    ~message() { delete reply_to_message; };
};
}

#endif // CPPGRAM_MESSAGE_H
