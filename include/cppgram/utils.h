#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#include <vector>
#include <string>

#define OSUTIL_NEWPROC_NOTSUPPORTED -1
#define OSUTIL_NEWPROC_SUCCESS 0
#define OSUTIL_NEWPROC_FAILED 1

#define SPLIT_FAILED -1
#define SPLIT_NOMORE_ONESTR 1
#define SPLIT_OK 0

namespace cppgram
{
    
namespace osutil
{
int backgroundProcess();    
}

namespace util
{
int split(const std::string& str,const char& splchr, std::vector<std::string>& vecstrs);
}

}
#endif //CPPGRAM_UTILS_H
