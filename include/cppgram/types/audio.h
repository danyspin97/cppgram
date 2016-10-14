#ifndef CPPGRAM_AUDIO_H
#define CPPGRAM_AUDIO_H

#include <string>

#include <json/json.h>

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Audio message sent by a user.
 * \details This object represents an audio file to be treated as music by the Telegram clients. (https://core.telegram.org/bots/api#audio) */
struct audio
{
    /** @} */

    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Duration of the audio in seconds as defined by sender */
    int_fast32_t duration;

    /** \brief <i>Optional</i>. Performer of the audio as defined by sender or by audio tags */
    std::string performer,

    /** \brief <i>Optional</i>. Title of the audio as defined by sender or by audio tags */
            title,

    /** \brief <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** \brief <i>Optional</i>. File size */
    int_fast32_t file_size;

    audio(Json::Value &jsonAudio) : file_id(jsonAudio["file_id"].asString()),
                                duration(jsonAudio["duration"].asUInt())
    {

        performer = !jsonAudio["performer"].isNull() ? jsonAudio["performer"].asString() : "";

        title = !jsonAudio["title"].isNull() ? jsonAudio["title"].asString() : "";

        mime_type = !jsonAudio["mime_type"].isNull() ? jsonAudio["mime_type"].asString() : "";

        file_size = !jsonAudio["file_size"].isNull() ? jsonAudio["file_size"].asUInt() : int_least32_t();
    };

    audio()
    {};

    ~audio()
    {};
};

}

#endif //CPPGRAM_AUDIO_H

