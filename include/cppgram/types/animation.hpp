#ifndef CPPGRAM_ANIMATION_HPP
#define CPPGRAM_ANIMATION_HPP

#include "photo_size.hpp"

namespace cppgram
{
namespace types
{
/** \class Animation
 * \brief This object represents an animation file to be displayed in the message containing a game.
 * [API reference](https://core.telegram.org/bots/api#animation)*/
class Animation
{
    public:
    /** \brief Unique file identifier. */
    std::string file_id;

    /** \brief <i>Optional</i>. Animation thumbnail as defined by sender. */
    std::experimental::optional<PhotoSize> thumb;

    /** \brief <i>Optional</i>. Original animation filename as defined by sender. */
    std::experimental::optional<std::string> file_name,

            /** <i>Optional</i>. MIME type of the file as defined by sender. */
            mime_type;

    /** \brief <i>Optional</i>. File size. */
    std::experimental::optional<uint_fast32_t> file_size;

    Animation( Json::Value &json_animation )
        : file_id( json_animation["file_id"].asString() )
    {
        if ( !json_animation["thumb"].isNull() )
        {
            thumb.emplace( PhotoSize( json_animation["thumb"] ) );
        }
        if ( !json_animation["file_name"].isNull() )
        {
            file_name.emplace( json_animation["file_name"].asString() );
        }
        if ( !json_animation["mime_type"].isNull() )
        {
            mime_type.emplace( json_animation["mime_type"].asString() );
        }
        if ( !json_animation["file_size"].isNull() )
        {
            file_size.emplace( json_animation["file_size"].asUInt() );
        }
    }
};
}
}

#endif
