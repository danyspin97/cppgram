#ifndef CPPGRAM_AUDIO_H
#define CPPGRAM_AUDIO_H

#include <string>

#include <json/json.h>

#include "integers.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** This object represents an audio file to be treated as music by the Telegram clients. (https://core.telegram.org/bots/api#audio) */
struct audio
{
    /** @} */

    /** Unique identifier for this file */
    std::string file_id;

    /** Duration of the audio in seconds as defined by sender */
    uid_32 duration;

    /** <i>Optional</i>. Performer of the audio as defined by sender or by audio tags */
    std::string performer,
    /** <i>Optional</i>. Title of the audio as defined by sender or by audio tags */
            title,

    /** <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** <i>Optional</i>. File size */
    uid_32 file_size;

    audio(Json::Value &audio) : file_id(audio["file_id"].asString()),
                                duration(audio["duration"].asUInt())
    {

        if (!audio["performer"].isNull())
            performer = audio["performer"].asString();

        if (!audio["title"].isNull())
            title = audio["title"].asString();

        if (!audio["mime_type"].isNull())
            mime_type = audio["mime_type"].asString();

        if (!audio["file_size"].isNull())
            file_size = audio["file_size"].asUInt();
    };
    audio()
    {};
    ~audio()
    {};
};

}

#endif //CPPGRAM_AUDIO_H
