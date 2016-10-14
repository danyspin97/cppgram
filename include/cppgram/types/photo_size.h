#ifndef CPPGRAM_PHOTO_SIZE_H
#define CPPGRAM_PHOTO_SIZE_H

#include <string>
#include <json/json.h>

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A photo or thumbnail
 * \details This object represents one size of a photo or a file / sticker thumbnail. (https://core.telegram.org/bots/api#photosize) */
struct photoSize
{
    /** @} */

    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Photo width */
    int_fast32_t width,

    /** \brief Photo height */
            height,

    /** \brief <i>Optional</i>. File size */
            file_size;

    photoSize(Json::Value &jsonPhotoSize)
            : file_id(jsonPhotoSize["file_id"].asString()),
              width(jsonPhotoSize["width"].asUInt()),
              height(jsonPhotoSize["height"].asUInt())
    {
        file_size = !jsonPhotoSize["file_size"].isNull() ? jsonPhotoSize["file_size"].asUInt() : int_fast32_t();

    };

    photoSize()
    {};

    ~photoSize()
    {};
};

}

#endif //CPPGRAM_PHOTO_SIZE_H
