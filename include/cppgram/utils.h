#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#include <vector>
#include <string>

#define OSUTIL_NEWPROC_NOTSUPPORTED -1
#define OSUTIL_NEWPROC_SUCCESS 0
#define OSUTIL_NEWPROC_FAILED 1
#define FILENAME_DEFAULT ".default_fname_logger"

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

std::vector<std::string> split(const std::string& str,const char& splchr);
std::string getTime(const std::string& timeformat="%a %F %r");
void log(const Log& l, const std::string& message, const std::string& filename=FILENAME_DEFAULT);

}

}
#endif //CPPGRAM_UTILS_H
