#ifndef CPPGRAM_VOICE_H
#define CPPGRAM_VOICE_H

#include <string>

#include <json/json.h>

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
    int_fast32_t duration;

    /** <i>Optional</i>. MIME type of the file as defined by sender */
    std::string mime_type;

    /** <i>Optional</i>. File size */
    int_fast32_t file_size;

    voice(Json::Value &jsonVoice)
            : file_id(jsonVoice["file_id"].asString()),
              duration(jsonVoice["duration"].asUInt())
    {
        mime_type = !jsonVoice["mime_type"].isNull() ? jsonVoice["mime_type"].asString() : "";

        file_size = !jsonVoice["file_size"].isNull() ? jsonVoice["file_size"].asUInt() : int_fast32_t();
    };

    voice()
    {};

    ~voice()
    {};
};

}

#endif //CPPGRAM_VOICE_H
