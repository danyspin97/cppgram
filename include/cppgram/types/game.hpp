#ifndef CPPGRAM_GAME_HPP
#define CPPGRAM_GAME_HPP

#include "animation.hpp"
#include "message_entity.hpp"
#include "photo_size.hpp"

namespace cppgram
{
class Game
{
    public:
    std::string                              title, description;
    std::vector<PhotoSize>                   photo;
    std::experimental::optional<std::string> text;
    std::vector<MessageEntity>               text_entities;
    std::experimental::optional<Animation>   animation;

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

#endif
