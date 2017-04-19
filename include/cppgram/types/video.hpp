#ifndef CPPGRAM_VIDEO_HPP
#define CPPGRAM_VIDEO_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

#include "photo_size.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief A video sent by user.
 * \details This object represents a video file. (https://core.telegram.org/bots/api#video) */
class Video
{
    /** @} */

    public:
    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Video width as defined by sender */
    uint_fast32_t width,

            /** \brief Video height as defined by sender */
            height,

            /** \brief Duration of the video in seconds as defined by sender */
            duration;

    /** \brief <i>Optional</i>. Video thumbnail */
    std::experimental::optional<PhotoSize> thumb;

    /** \brief <i>Optional</i>. Mime type of a file as defined by sender */
    std::experimental::optional<std::string> mime_type;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<uint_fast32_t> file_size;

    Video( Json::Value &json_video )
        : file_id( json_video["file_id"].asString() )
        , width( json_video["width"].asUInt() )
        , height( json_video["height"].asUInt() )
        , duration( json_video["duration"].asUInt() )
    {
        if ( !json_video["thumb"].isNull() )
        {
            thumb.emplace( PhotoSize( json_video["thumb"] ) );
        }

        if ( !json_video["mime_type"].isNull() )
        {
            mime_type.emplace( json_video["mime_type"].asString() );
        }

        if ( !json_video["file_size"].isNull() )
        {
            file_size.emplace( json_video["file_size"].asUInt() );
        }
    }
};
}
}

#endif
