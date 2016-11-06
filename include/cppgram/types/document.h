#ifndef CPPGRAM_DOCUMENT_H
#define CPPGRAM_DOCUMENT_H

#include <string>

#include <json/json.h>

#include "photo_size.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A document send by a user
 * \details This object represents a general file (as opposed to photos, voice messages and audio files). [Api reference](https://core.telegram.org/bots/api#document) */
struct document
{
    /** @} */

    /** \brief Unique file identifier */
    std::string file_id;

    /** \brief <i>Optional</i>. Document thumbnail as defined by sender */
    std::experimental::optional<cppgram::photoSize> thumb;

    /** \brief <i>Optional</i>. Original filename as defined by sender */
    std::experimental::optional<std::string> file_name,

    /** \brief <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<int_fast32_t> file_size;

    document()
    {};

    document(Json::Value &jsonDocument) : file_id(jsonDocument["file_id"].asString())
    {

        thumb.emplace(photoSize(jsonDocument["thumb"]));

        file_name.emplace(jsonDocument["file_name"].asString());

        mime_type.emplace(jsonDocument["mime_type"].asString());

        file_size.emplace(jsonDocument["file_size"].asUInt());

    }

};

}
#endif //CPPGRAM_DOCUMENT_H
