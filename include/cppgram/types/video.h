#ifndef CPPGRAM_VIDEO_H
#define CPPGRAM_VIDEO_H

#include <string>

#include <json/json.h>

#include "photo_size.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A video sent by user.
 * \details This object represents a video file. (https://core.telegram.org/bots/api#video) */
struct video
{
    /** @} */

    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Video width as defined by sender */
    int_fast32_t width,

    /** \brief Video height as defined by sender */
            height,

    /** \brief Duration of the video in seconds as defined by sender */
            duration;

    /** \brief <i>Optional</i>. Video thumbnail */
    struct photoSize *thumb;

    /** \brief <i>Optional</i>. Mime type of a file as defined by sender */
    std::string mime_type;

    /** \brief <i>Optional</i>. File size */
    int_fast32_t file_size;

    video(Json::Value &jsonVideo)
            : file_id(jsonVideo["file_id"].asString()),
              width(jsonVideo["width"].asUInt()),
              height(jsonVideo["height"].asUInt()),
              duration(jsonVideo["duration"].asUInt())
    {
        thumb = !jsonVideo["thumb"].isNull() ? new photoSize(jsonVideo["thumb"]) : nullptr;


        mime_type = !jsonVideo["mime_type"].isNull() ? jsonVideo["mime_type"].asString() : "";


        file_size = !jsonVideo["file_size"].isNull() ? jsonVideo["file_size"].asUInt() : int_fast32_t();
    }

    video()
    {};

    ~video()
    { if (thumb != NULL) delete thumb; };
};

}

#endif //CPPGRAM_VIDEO_H
