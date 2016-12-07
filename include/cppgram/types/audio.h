#ifndef CPPGRAM_AUDIO_H
#define CPPGRAM_AUDIO_H

#include <string>
#include <experimental/optional>

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
    std::experimental::optional<std::string> performer,

    /** \brief <i>Optional</i>. Title of the audio as defined by sender or by audio tags */
            title,

    /** \brief <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<int_fast32_t> file_size;

    audio(Json::Value &jsonAudio)
        : file_id(jsonAudio["file_id"].asString()),
          duration(jsonAudio["duration"].asUInt())
    {

        if (!jsonAudio["performer"].isNull())
        {
            performer.emplace(jsonAudio["performer"].asString());
        }

        if (!jsonAudio["title"].isNull())
        {
            title.emplace(jsonAudio["title"].asString());
        }

        if (!jsonAudio["mime_type"].isNull())
        {
            mime_type.emplace(jsonAudio["mime_type"].asString());
        }

        if (!jsonAudio["file_size"].isNull())
        {
            file_size.emplace(jsonAudio["file_size"].asUInt());
        }

    };

    audio()
    {};

};

}

#endif //CPPGRAM_AUDIO_H

