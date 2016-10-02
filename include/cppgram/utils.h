#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#include <vector>
#include <string>

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

/*! \namespace cppgram::util
 * \brief User-availible utilities :)
 */
namespace util
{

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
void log(const Log& l, const std::string& message, const std::string& filename=FILENAME_DEFAULT);

/*!
 * \brief parses response's JSON and checks for error codes
 * \param response : the cpr::Response object
 * \param val : the target Json::Value 's reference
 * \return true if everything OK, else: false
 */
bool checkMethodError(const cpr::Response &response, Json::Value &val);
}

}

#endif //CPPGRAM_UTILS_H
