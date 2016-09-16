#ifndef CPPGRAM_UTILS_H
#define CPPGRAM_UTILS_H

#define OSUTIL_NEWPROC_NOTSUPPORTED -1
#define OSUTIL_NEWPROC_SUCCESS 0
#define OSUTIL_NEWPROC_FAILED 1

#include<string>
#include<vector>

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
