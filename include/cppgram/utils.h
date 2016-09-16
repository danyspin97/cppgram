#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#include <vector>
#include <string>

#define OSUTIL_NEWPROC_NOTSUPPORTED -1
#define OSUTIL_NEWPROC_SUCCESS 0
#define OSUTIL_NEWPROC_FAILED 1

namespace cppgram
{
    
namespace osutil
{
int backgroundProcess();    
}

namespace util
{
std::vector<std::string> split(const std::string& str,const char& splchr);
}

}
#endif //CPPGRAM_UTILS_H
