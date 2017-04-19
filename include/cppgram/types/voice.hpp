#ifndef CPPGRAM_VOICE_HPP
#define CPPGRAM_VOICE_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** This object represents a voice note. (https://core.telegram.org/bots/api#voice) */
class Voice
{
    /** @} */

    public:
    /** Unique identifier for this file */
    std::string file_id;

    /** Duration of the audio in seconds as defined by sender */
    uint_fast32_t duration;

    /** <i>Optional</i>. MIME type of the file as defined by sender */
    std::experimental::optional<std::string> mime_type;

    /** <i>Optional</i>. File size */
    std::experimental::optional<uint_fast32_t> file_size;

    Voice( Json::Value &json_voice )
        : file_id( json_voice["file_id"].asString() )
        , duration( json_voice["duration"].asUInt() )
    {
        if ( !json_voice["mime_type"].isNull() )
        {
            mime_type.emplace( json_voice["mime_type"].asString() );
        }

        if ( !json_voice["file_size"].isNull() )
        {
            file_size.emplace( json_voice["file_size"].asUInt() );
        }
    };
};
}
}

#endif
