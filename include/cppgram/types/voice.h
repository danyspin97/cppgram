#ifndef CPPGRAM_VOICE_H
#define CPPGRAM_VOICE_H

#include <string>

#include <json/json.h>

#include "integers.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** This object represents a voice note. (https://core.telegram.org/bots/api#voice) */
struct voice
{
    /** @} */

    /** Unique identifier for this file */
    std::string file_id;

    /** Duration of the audio in seconds as defined by sender */
    uid_32 duration;

    /** <i>Optional</i>. MIME type of the file as defined by sender */
    std::string mime_type;

    /** <i>Optional</i>. File size */
    uid_32 file_size;

    voice(Json::Value &voice) : file_id(voice["file_id"].asString()), duration(voice["duration"].asUInt())
    {
        if (!voice["mime_type"].isNull())
            mime_type = voice["mime_type"].asString();

        if (!voice["file_size"].isNull())
            file_size = voice["file_size"].asUInt();
    };

    voice()
    {};
    ~voice()
    {};
};

}

#endif //CPPGRAM_VOICE_H
