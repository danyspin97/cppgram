#ifndef CPPGRAM_DOCUMENT_HPP
#define CPPGRAM_DOCUMENT_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

#include "photo_size.hpp"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief A document send by a user
 * \details This object represents a general file (as opposed to photos, voice messages and audio
 * files). [Api reference](https://core.telegram.org/bots/api#document) */
class Document
{
    /** @} */

    public:
    /** \brief Unique file identifier */
    std::string file_id;

    /** \brief <i>Optional</i>. Document thumbnail as defined by sender */
    std::experimental::optional<PhotoSize> thumb;

    /** \brief <i>Optional</i>. Original filename as defined by sender */
    std::experimental::optional<std::string> file_name,

            /** \brief <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<int_fast32_t> file_size;

    Document( Json::Value &json_document )
        : file_id( json_document["file_id"].asString() )
    {
        if ( !json_document["thumb"].isNull() )
        {
            thumb.emplace( PhotoSize( json_document["thumb"] ) );
        }

        if ( !json_document["file_name"].isNull() )
        {
            file_name.emplace( json_document["file_name"].asString() );
        }

        if ( !json_document["mime_type"].isNull() )
        {
            mime_type.emplace( json_document["mime_type"].asString() );
        }

        if ( !json_document["file_size"].isNull() )
        {
            file_size.emplace( json_document["file_size"].asUInt() );
        }
    }
};
}
#endif
