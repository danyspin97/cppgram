#ifndef CPPGRAM_PHOTO_SIZE_HPP
#define CPPGRAM_PHOTO_SIZE_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief A photo or thumbnail
 * \details This object represents one size of a photo or a file / sticker thumbnail.
 * (https://core.telegram.org/bots/api#photosize) */
class PhotoSize
{
    /** @} */

    public:
    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Photo width */
    uint_fast32_t width,

            /** \brief Photo height */
            height;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<uint32_t> file_size;

    PhotoSize( Json::Value &json_photo_size )
        : file_id( json_photo_size["file_id"].asString() )
        , width( json_photo_size["width"].asUInt() )
        , height( json_photo_size["height"].asUInt() )
    {
        if ( !json_photo_size["file_size"].isNull() )
        {
            file_size.emplace( json_photo_size["file_size"].asUInt() );
        }
    };
};
}

#endif
