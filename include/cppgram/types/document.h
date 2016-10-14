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
 * \details This object represents a general file (as opposed to photos, voice messages and audio files). (https://core.telegram.org/bots/api#document) */
struct document
{
    /** @} */

    /** \brief Unique file identifier */
    std::string file_id;

    /** \brief <i>Optional</i>. Document thumbnail as defined by sender */
    struct photoSize *thumb;

    /** \brief <i>Optional</i>. Original filename as defined by sender */
    std::string file_name,

    /** \brief <i>Optional</i>. MIME type of the file as defined by sender */
            mime_type;

    /** \brief <i>Optional</i>. File size */
    int_fast32_t file_size;

    document(Json::Value &jsonDocument) : file_id(jsonDocument["file_id"].asString())
    {
        thumb = !jsonDocument["thumb"].isNull() ? new photoSize(jsonDocument["thumb"]) : nullptr;

        file_name = !jsonDocument["file_name"].isNull() ? jsonDocument["file_name"].asString() : "";

        mime_type  = !jsonDocument["mime_type"].isNull() ? jsonDocument["mime_type"].asString() : "";

        file_size = !jsonDocument["file_size"].isNull() ? jsonDocument["file_size"].asUInt() : int_fast32_t();
    }

    document()
    {};

    ~document()
    { if (thumb != NULL) delete thumb; };
};

}
#endif //CPPGRAM_DOCUMENT_H
