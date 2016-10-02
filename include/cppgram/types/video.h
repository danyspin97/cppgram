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

/** This object represents a video file. (https://core.telegram.org/bots/api#video) */
struct video
{
    /** @} */

    /** Unique identifier for this file */
    std::string file_id;

    /** Video width as defined by sender */
    uid_32 width,

    /** Video height as defined by sender */
            height,

    /** Duration of the video in seconds as defined by sender */
            duration;

    /** <i>Optional</i>. Video thumbnail */
    struct photoSize *thumb;

    /** <i>Optional</i>. Mime type of a file as defined by sender */
    std::string mime_type;

    /** <i>Optional</i>. File size */
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
