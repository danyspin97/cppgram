#ifndef CPPGRAM_LOCATION_H
#define CPPGRAM_LOCATION_H

#include <string>

#include <json/json.h>

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief A location send by a user.
 * \details This object represents a point on the map. (https://core.telegram.org/bots/api#location) */
struct location
{
    /** @} */

    /** \brief Longitude as defined by sender */
    float longitude,

    /** \brief Latitude as defined by sender */
            latidute;

    location(Json::Value &jsonLocation)
            : longitude(jsonLocation["longitude"].asFloat()),
              latidute(jsonLocation["latidute"].asFloat())
    {}

    location()
    {}

};

}

#endif //CPPGRAM_LOCATION_H
