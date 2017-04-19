#ifndef CPPGRAM_STICKER_HPP
#define CPPGRAM_STICKER_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

#include "photo_size.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief A sticker
 * \details This object represents a sticker. (https://core.telegram.org/bots/api#sticker) */
class Sticker
{
    /** @} */

    public:
    /** \brief Unique identifier for this file */
    std::string file_id;

    /** \brief Sticker width */
    uint_fast32_t width,

            /** \brief Sticker height */
            height;

    /** \brief <i>Optional</i>. Sticker thumbnail in .webbp or .jpg format */
    std::experimental::optional<PhotoSize> thumb;

    /** \brief <i>Optional</i>. Emoj associated with the sticker */
    std::experimental::optional<std::string> emoj;

    /** \brief <i>Optional</i>. File size */
    std::experimental::optional<uint_fast32_t> file_size;

    Sticker( Json::Value &json_sticker )
        : file_id( json_sticker["file_id"].asString() )
        , width( json_sticker["width"].asUInt() )
        , height( json_sticker["height"].asUInt() )
    {
        if ( !json_sticker["thumb"].isNull() )
        {
            thumb.emplace( PhotoSize( json_sticker["thumb"] ) );
        }

        if ( !json_sticker["emoj"].isNull() )
        {
            emoj.emplace( json_sticker["emoj"].asString() );
        }

        if ( !json_sticker["file_size"].isNull() )
        {
            file_size.emplace( json_sticker["file_size"].asUInt() );
        }
    }
};
}
}

#endif
