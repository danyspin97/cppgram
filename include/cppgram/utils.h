#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#include <vector>
#include <string>

#include "defines.h"

namespace cppgram
{

namespace osutil
{
int backgroundProcess();    
}

namespace util
{

enum Log 
{
    Event,
    Error,
    Warning
};

const std::vector<std::string> split(const std::string& str,const char& splchr);
const std::string getTime(const std::string& timeformat="%a %F %r");
void log(const Log& l, const std::string& message, const std::string& filename=FILENAME_DEFAULT);

}

}

#endif //CPPGRAM_UTILS_H
