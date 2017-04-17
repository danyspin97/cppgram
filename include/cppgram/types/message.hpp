#ifndef CPPGRAM_MESSAGE_HPP
#define CPPGRAM_MESSAGE_HPP

#include <experimental/optional>
#include <memory>
#include <string>

#include <json/json.h>

#include "audio.hpp"
#include "chat.hpp"
#include "contact.hpp"
#include "document.hpp"
#include "game.hpp"
#include "location.hpp"
#include "message_entity.hpp"
#include "message_entity.hpp"
#include "sticker.hpp"
#include "user.hpp"
#include "venue.hpp"
#include "video.hpp"
#include "voice.hpp"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/**
 * \class Message
 * \brief A message send by user.
 * \details This object represents a message. (https://core.telegram.org/bots/api#message) */
class Message
{
    /** @} */

    public:
    /** \brief Unique message identifier */
    uint_fast32_t message_id;

    /** \brief <i>Optional</i>. Sender, can be empty for messages sent to channels */
    std::experimental::optional<User> from;

    /** \brief Date the message was sent in Unix time */
    uint_fast32_t date;

    /** \brief Conversation the message belongs to */
    Chat chat;

    /** \brief <i>Optional</i>. For forwarded messages, sender of the original message */
    std::experimental::optional<User> forward_from;

    /** \brief <i>Optional</i>. For messages forwarded from a channel, information about the
     * original channel */
    std::experimental::optional<Chat> forward_from_chat;

    /** \brief <i>Optional</i>. For forwarded messages, date the original message was sent in Unix
     * time */
    std::experimental::optional<uint_fast32_t> forward_date;

    /** \brief <i>Optional</i>. For replies, the original message. Note that the Message object in
     * this field will not contain further reply_to_message fields even if it itself is a reply. */
    std::shared_ptr<Message> reply_to_message;

    /** \brief <i>Optional</i>. Date the message was last edited in Unix time */
    std::experimental::optional<uint_fast32_t> edit_date;

    /** \brief <i>Optional</i>. For text messages, the actual UTF-8 text of the message, 0-4096
     * characters. */
    std::experimental::optional<std::string> text;

    /** \brief <i>Optional</i>. For text messages, an array of messageEntinty */
    std::vector<MessageEntity> entities;

    /** \brief <i>Optional</i>. Message is an audio file, information about the file */
    std::experimental::optional<Audio> audio;

    /** \brief <i>Optional</i>. Message is a general file, information about the file */
    std::experimental::optional<Document> document;

    std::experimental::optional<Game> game;

    /** \brief <i>Optional</i>. Message is a photo, available sizes of the photo */
    std::vector<PhotoSize> photo;

    /** \brief<i>Optional</i>. Message is a sticker, information about the sticker */
    std::experimental::optional<Sticker> sticker;

    /** \brief <i>Optional</i>. Message is a video, information about the video */
    std::experimental::optional<Video> video;

    /** \brief <i>Optional</i>. Message is a voice message, information about the file */
    std::experimental::optional<Voice> voice;

    /** \brief <i>Optional</i>. Message is a shared contact, information about the contact */
    std::experimental::optional<Contact> contact;

    /** \brief <i>Optional</i>. Message is a shared location, information about the location */
    std::experimental::optional<Location> location;

    /** \brief <i>Optional</i>. Message is a venue, information about the venue */
    std::experimental::optional<Venue> venue;

    /** \brief <i>Optional</i>. Caption for the document, photo or video, 0-200 characters */
    std::experimental::optional<std::string> caption;

    /** \brief <i>Optional</i>. A new member was added to the group, information about them (this
     * member may be the bot itself). */
    std::experimental::optional<User> new_chat_member;

    /** \brief <i>Optional</i>. A member was removed from the group, information about them (this
     * member may be the bot itself). */
    std::experimental::optional<User> left_chat_member;

    /** \brief <i>Optional</i>. A chat title was changed to this value. */
    std::experimental::optional<std::string> new_chat_title;

    /** \brief <i>Optional</i>. A chat photo was change to this value. */
    std::vector<PhotoSize> new_chat_photo;

    /** \brief Service message. @see ServiceMessage */
    ServiceMessage service_message;

    /** \brief <i>Optional</i>. The group has been migrated to a supergroup with the specified
     * identifier. This number may be greater than 32 bits and some programming languages may have
     * difficulty/silent defects in interpreting it. But it is smaller than 52 bits, so a signed 64
     * bit integer or double-precision float type are safe for storing this identifier. */
    std::experimental::optional<uint_fast64_t> migrate_to_chat_id,

            /*** \brief <i>Optional</i>. The supergroup has been migrated from a group with the
               specified identifier. This number may be greater than 32 bits and some programming
               languages may have difficulty/silent defects in interpreting it. But it is smaller
               than 52 bits, so a signed 64 bit integer or double-precision float type are safe for
               storing this identifier. */
            migrate_from_chat_id;

    /** \brief <i>Optional</i>. Specified message was pinned. Note that the Message object in this
     * field will not contain further reply_to_message fields even if it is itself a reply. */
    std::shared_ptr<Message> pinned_message;

    Message( Json::Value &json_message )
        : message_id( json_message["message_id"].asUInt() )
        , date( json_message["date"].asUInt() )
        , chat( json_message["chat"] )
    {
        if ( !json_message["from"].isNull() )
        {
            from.emplace( User( json_message["from"] ) );
        }

        if ( !json_message["forward_from"].isNull() )
        {
            forward_from.emplace( User( json_message["forward_from"] ) );
            forward_from_chat.emplace( Chat( json_message["forward_from_chat"] ) );
            forward_date.emplace( json_message["forward_date"].asUInt() );
        }

        if ( !json_message["reply_to_message"].isNull() )
        {
            reply_to_message
                    = std::make_shared<Message>( Message( json_message["reply_to_message"] ) );
        }
        else
        {
            reply_to_message = nullptr;
        }

        if ( !json_message["edit_date"].isNull() )
        {
            edit_date.emplace( json_message["edit_date"].asUInt() );
        }

        if ( !json_message["text"].isNull() )
        {
            text.emplace( json_message["text"].asString() );
        }

        entities.reserve( json_message["entities"].size() );
        if ( !json_message["entities"].isNull() )
        {
            for ( Json::Value &json_entity : json_message["entities"] )
            {
                entities.push_back( MessageEntity( json_entity ) );
            }
        }

        if ( !json_message["audio"].isNull() )
        {
            audio.emplace( Audio( json_message["audio"] ) );
        }
        else if ( !json_message["document"].isNull() )
        {
            document.emplace( Document( json_message["document"] ) );
        }
        else if ( !json_message["game"].isNull() )
        {
            game.emplace( Game( json_message["game"] ) );
        }
        else if ( !json_message["photo"].isNull() )
        {
            photo.reserve( json_message["photo"].size() );
            for ( Json::Value &json_photo : json_message["photo"] )
            {
                photo.push_back( PhotoSize( json_photo ) );
            }
        }
        else if ( !json_message["sticker"].isNull() )
        {
            sticker.emplace( Sticker( json_message["sticker"] ) );
        }
        else if ( !json_message["video"].isNull() )
        {
            video.emplace( Video( json_message["video"] ) );
        }
        else if ( !json_message["voice"].isNull() )
        {
            voice.emplace( Voice( json_message["voice"] ) );
        }
        else if ( !json_message["contact"].isNull() )
        {
            contact.emplace( Contact( json_message["contact"] ) );
        }
        else if ( !json_message["location"].isNull() )
        {
            location.emplace( Location( json_message["location"] ) );
        }
        else if ( !json_message["venue"].isNull() )
        {
            venue.emplace( Venue( json_message["venue"] ) );
        }

        if ( !json_message["caption"].isNull() )
        {
            caption = json_message["caption"].asString();
        }

        if ( !json_message["new_chat_member"].isNull() )
        {
            new_chat_member.emplace( User( json_message["new_chat_member"] ) );
            ;
        }

        if ( !json_message["left_chat_member"].isNull() )
        {
            left_chat_member.emplace( User( json_message["left_chat_member"] ) );
        }

        if ( !json_message["new_chat_photo"].empty() )
        {
            new_chat_photo.reserve( json_message["new_chat_photo"].size() );
            for ( Json::Value &json_photo : json_message["new_chat_photo"] )
            {
                new_chat_photo.push_back( PhotoSize( json_photo ) );
            }
        }

        if ( !json_message["delete_chat_photo"].isNull() )
        {
            service_message = ServiceMessage::delete_chat_photo;
        }
        else if ( !json_message["group_chat_created"].isNull() )

        {
            service_message = ServiceMessage::group_chat_created;
        }
        else if ( !json_message["supergroup_chat_created"].isNull() )
        {
            service_message = ServiceMessage::supergroup_chat_created;
        }
        else if ( !json_message["channel_chat_created"].isNull() )
        {
            service_message = ServiceMessage::channel_chat_created;
        }

        if ( !json_message["migrate_to_chat_id"].isNull() )
        {
            migrate_to_chat_id.emplace( json_message["migrate_to_chat_id"].asInt64() );
        }

        if ( !json_message["migrate_from_chat_id"].isNull() )
        {
            migrate_from_chat_id.emplace( json_message["migrate_from_chat_id"].asInt64() );
        }

        if ( !json_message["pinned_message"].isNull() )
        {
            pinned_message = std::make_shared<Message>( Message( json_message["pinned_message"] ) );
        }
    }

    Message() {}
};
}

#endif
