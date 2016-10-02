#ifndef CPPGRAM_LOCATION_H
#define CPPGRAM_LOCATION_H

#include <string>

#include <json/json.h>

#include "integers.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** This object represents a point on the map. (https://core.telegram.org/bots/api#location) */
struct location
{
    /** @} */

    /** Longitude as defined by sender */
    float longitude,

    /** Latitude as defined by sender */
            latidute;

    location(Json::Value &location)
            : longitude(location["longitude"].asFloat()), latidute(location["latidute"].asFloat())
    {}

    location()
    {}

    ~location()
    {}
};

}

#endif //CPPGRAM_LOCATION_H
