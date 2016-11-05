#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#include <vector>
#include <string>

#include <sys/time.h>

#include "defines.h"

namespace cpr
{
typedef std::string Url;
class Parameters;
class Response;
}

namespace Json
{
class Value;
}

namespace cppgram
{

//this will not be documented
namespace osutil
{
int backgroundProcess();
}
// ...

/*! \enum Log
 * \brief used inside the log() function, can be used to specify the log type
 */
enum Log
{
    Event,
    Error,
    Warning
};

/*!
 * \brief splits a string
 * \param str: the main string
 * \param splchr: the split character
 * \return a vector of splitted
 */
const std::vector<std::string> split(const std::string& str,const char& splchr);
/*!
 * \brief gets time from unix date
 * \param timeformat: formatted time string
 * \return formatted time, as specified in timeformat arg
 */
const std::string getTime(const std::string& timeformat="%a %F %r");
/*!
 * \brief logs an event/error/warning, can change its predefined filename
 * \param l: specify the Log type (Event/Error/Warning)
 * \param message: specify the message to be logged
 * \param filename: specify a custom filenames
 */
void log(const Log& logType, const std::string& message, const std::string& filename = "tg_bot.log");

/*!
 * \brief parses response's JSON and checks for error codes
 * \param response : the cpr::Response object
 * \param val : the target Json::Value 's reference
 * \return true if everything OK, else: false
 */
bool checkMethodError(const cpr::Response &response, Json::Value &val);

inline int_fast64_t getMicroTime()
{
    struct timeval tv;

    gettimeofday(&tv, NULL);

    int_fast64_t ret = tv.tv_usec;
    /* Convert from micro seconds (10^-6) to milliseconds (10^-3) */
    ret /= 1000;

    /* Adds the seconds (10^0) after converting them to milliseconds (10^-3) */
    ret += (tv.tv_sec * 1000);

    return ret;
}
}

#endif //CPPGRAM_UTILS_H
