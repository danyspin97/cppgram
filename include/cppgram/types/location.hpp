#ifndef CPPGRAM_LOCATION_HPP
#define CPPGRAM_LOCATION_HPP

#include <string>

#include <json/json.h>

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief A location send by a user.
 * \details This object represents a point on the map. (https://core.telegram.org/bots/api#location)
 */
class Location
{
    /** @} */

    public:
    /** \brief Longitude as defined by sender */
    float longitude,

            /** \brief Latitude as defined by sender */
            latidute;

    Location( Json::Value &json_location )
        : longitude( json_location["longitude"].asFloat() )
        , latidute( json_location["latidute"].asFloat() )
    {
    }
};
}
}

#endif
