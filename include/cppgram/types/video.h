#ifndef CPPGRAM_VIDEO_H
#define CPPGRAM_VIDEO_H

#include <string>

#include <json/json.h>

#include "integers.h"
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
    uid_32 width,

    /** \brief Video height as defined by sender */
            height,

    /** \brief Duration of the video in seconds as defined by sender */
            duration;

    /** \brief <i>Optional</i>. Video thumbnail */
    struct photoSize *thumb;

    /** \brief <i>Optional</i>. Mime type of a file as defined by sender */
    std::string mime_type;

    /** \brief <i>Optional</i>. File size */
    uid_32 file_size;

    video(Json::Value &video)
            : file_id(video["file_id"].asString()),
              width(video["width"].asUInt()),
              height(video["height"].asUInt()),
              duration(video["duration"].asUInt())
    {
        if (!video["thumb"].isNull())
            thumb = new photoSize(video["thumb"]);

        if (!video["mime_type"].isNull())
            mime_type = video["mime_type"].asString();

        if (!video["file_size"].isNull())
            file_size = video["file_size"].asUInt();
    }

    video()
    {};

    ~video()
    { if (thumb != NULL) delete thumb; };
};

}

#endif //CPPGRAM_VIDEO_H
