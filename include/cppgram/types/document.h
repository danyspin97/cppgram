#ifndef CPPGRAM_DOCUMENT_H
#define CPPGRAM_DOCUMENT_H

#include <string>

#include <json/json.h>

#include "integers.h"
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
    uid_32 file_size;

    document(Json::Value &document) : file_id(document["file_id"].asString())
    {
        if (!document["thumb"].isNull())
            thumb = new photoSize(document["thumb"]);

        if (!document["file_name"].isNull())
            file_name = document["file_name"].asString();

        if (!document["mime_type"].isNull())
            mime_type  = document["mime_type"].asString();

        if (!document["file_size"].isNull())
            file_size = document["file_size"].asUInt();
    }

    document();

    ~document()
    { if (thumb != NULL) delete thumb; };
};

}
#endif //CPPGRAM_DOCUMENT_H
