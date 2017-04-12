#ifndef CPPGRAM_ANIMATION_HPP
#define CPPGRAM_ANIMATION_HPP

#include "photo_size.hpp"

namespace cppgram
{
class Animation
{
    public:

        std::string file_id;
        std::experimental::optional<PhotoSize> thumb;
        std::experimental::optional<std::string> file_name, mime_type;
        std::experimental::optional<uint_fast32_t> file_size;

        Animation(Json::Value& json_animation)
            : file_id (json_animation["file_id"].asString())
        {
            if (!json_animation["thumb"].isNull())
            {
                thumb.emplace(PhotoSize(json_animation["thumb"]));
            }
            if (!json_animation["file_name"].isNull())
            {
                file_name.emplace(json_animation["file_name"].asString());
            }
            if (!json_animation["mime_type"].isNull())
            {
                mime_type.emplace(json_animation["mime_type"].asString());
            }
            if (!json_animation["file_size"].isNull())
            {
                file_size.emplace(json_animation["file_size"].asUInt());
            }
        }
};
}

#endif
