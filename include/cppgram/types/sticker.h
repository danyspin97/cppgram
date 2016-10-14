#ifndef CPPGRAM_STICKER_H
#define CPPGRAM_STICKER_H

#include <string>

#include <json/json.h>

#include "photo_size.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A sticker
 * \details This object represents a sticker. (https://core.telegram.org/bots/api#sticker) */
struct sticker
{
    /** @} */

    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Sticker width */
    int_fast32_t width,

    /** \brief Sticker height */
            height;

    /** \brief <i>Optional</i>. Sticker thumbnail in .webbp or .jpg format */
    struct photoSize *thumb;

    /** \brief <i>Optional</i>. Emoj associated with the sticker */
    std::string emoj;

    /** \brief <i>Optional</i>. File size */
    int_fast32_t file_size;

    sticker(Json::Value &sticker)
            : file_id(sticker["file_id"].asString()),
              width(sticker["width"].asUInt()),
              height(sticker["height"].asUInt())
    {
        thumb = !sticker["thumb"].isNull() ? new photoSize(sticker["thumb"]) : nullptr;

        emoj = !sticker["emoj"].isNull() ? sticker["emoj"].asString() : "";

        file_size = !sticker["file_size"].isNull() ? sticker["file_size"].asUInt() : int_fast32_t();
    }

    sticker()
    {}

    ~sticker()
    { if (thumb != NULL) delete thumb; };
};

}

#endif //CPPGRAM_STICKER_H
