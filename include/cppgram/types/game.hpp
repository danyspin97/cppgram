#ifndef CPPGRAM_GAME_HPP
#define CPPGRAM_GAME_HPP

#include "animation.hpp"
#include "message_entity.hpp"
#include "photo_size.hpp"

namespace cppgram
{
namespace types
{
/**
 * \class Game
 *  \brief This object represents a game.
 *  \details Use BotFather to create and edit games, their short names will act as unique
 * identifiers. [Api Reference](https://core.telegram.org/bots/api#games)
 */
class Game
{
    public:
    /** \brief Title of the game. */
    std::string title,

            /** \brief Description of the game. */
            description;

    /** \brief Photo that will be displayed in the game message in chats. */
    std::vector<PhotoSize> photo;
    /** \brief <i>Optional</i>. Brief description of the game or high scores included in the game
     * message.
     * Can be automatically edited to include current high scores for the game when the bot calls
     * setGameScore, or manually edited using editMessageText. 0-4096 characters. */
    std::experimental::optional<std::string> text;
    /** \brief <i>Optional</i>. Special entities that appear in text, such as usernames, URLs, bot
     * commands, etc. */
    std::vector<MessageEntity> text_entities;
    /** \brief <i>Optional</i>. Animation that will be displayed in the game message in chats.
     * Upload via BotFather. */
    std::experimental::optional<Animation> animation;

    Game( Json::Value &json_game )
        : title( json_game["title"].asString() )
        , description( json_game["description"].asString() )
    {
        photo.reserve( json_game["photo"].size() );
        for ( Json::Value &json_photo : json_game["photo"] )
        {
            photo.push_back( PhotoSize( json_photo ) );
        }

        if ( !json_game["text"].isNull() )
        {
            text.emplace( json_game["text"].asString() );
        }

        text_entities.reserve( json_game["text_entities"].size() );
        for ( Json::Value &json_entity : json_game["text_entities"] )
        {
            text_entities.push_back( MessageEntity( json_entity ) );
        }

        if ( !json_game["animation"].isNull() )
        {
            animation.emplace( Animation( json_game["animation"] ) );
        }
    }
};
}
}

#endif
