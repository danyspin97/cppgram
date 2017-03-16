#ifndef CPPGRAM_VENUE_HPP
#define CPPGRAM_VENUE_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

#include "location.hpp"

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief This object represents a venue.
 * \details (https://core.telegram.org/bots/api#venue) */
class Venue
{
    /** @} */

    public:
    /** \brief Venue location */
    Location location;

    /** \brief Name of the venue */
    std::string title,

            /** \brief Address of the venue */
            address;

    /** \brief <i>Optional</i>. Foursquare identifier of the venue */
    std::experimental::optional<std::string> foursquare_id;

    Venue( Json::Value &json_venue )
        : location( Location( json_venue["location"] ) )
        , title( json_venue["title"].asString() )
        , address( json_venue["address"].asString() )
    {
        if ( !json_venue["foursquare_id"].isNull() )
        {
            foursquare_id.emplace( json_venue["foursquare_id"].asString() );
        }
    }
};
}

#endif
