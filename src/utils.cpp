#ifdef __unix__
#include<unistd.h>
#include<stdlib.h>
#endif

#include <sstream>

#include "cppgram/utils.h"

int cppgram::osutil::backgroundProcess()
{
#ifdef __gnu_linux__
    pid_t procid;

    procid=fork();
	 switch(procid) {
		 case -1:
			 return OSUTIL_NEWPROC_FAILED;
		 case 0:
			 break;
		 default:
			 exit(0);
	 }

    if(setsid() < 0) return OSUTIL_NEWPROC_FAILED;

    /*close file descriptors*/
    close(0);
    close(1);
    close(2);

    return OSUTIL_NEWPROC_SUCCESS;
#else
    return OSUTIL_NEWPROC_NOTSUPPORTED;
#endif
}

std::vector<std::string> cppgram::util::split(const std::string& str, const char& splchr)
{
    std::vector<std::string> vecstrs;
    std::stringstream ss;
    std::string item;
    
    ss.str(str);
    
    while (getline(ss, item, splchr)) {
        vecstrs.push_back(item);
    }

    return vecstrs;
}
