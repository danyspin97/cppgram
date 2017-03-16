#ifndef CPPGRAM_AUDIO_HPP
#define CPPGRAM_AUDIO_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief Audio message sent by a user.
 * \details This object represents an audio file to be treated as music by the Telegram clients.
 * (https://core.telegram.org/bots/api#audio) */
class Audio
{
    /** @} */

    public:
    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Duration of the audio in seconds as defined by sender */
    uint_fast32_t duration;

    /** \brief <i>Optional</i>. Performer of the audio as defined by sender or by audio tags */
    std::experimental::optional<std::string> performer,

            /** \brief <i>Optional</i>. Title of the audio as defined by sender or by audio tags */
            title,

            /** \brief <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<int_fast32_t> file_size;

    Audio( Json::Value &json_audio )
        : file_id( json_audio["file_id"].asString() )
        , duration( json_audio["duration"].asUInt() )
    {
        if ( !json_audio["performer"].isNull() )
        {
            performer.emplace( json_audio["performer"].asString() );
        }

        if ( !json_audio["title"].isNull() )
        {
            title.emplace( json_audio["title"].asString() );
        }

        if ( !json_audio["mime_type"].isNull() )
        {
            mime_type.emplace( json_audio["mime_type"].asString() );
        }

        if ( !json_audio["file_size"].isNull() )
        {
            file_size.emplace( json_audio["file_size"].asUInt() );
        }
    };
};
}

#endif
