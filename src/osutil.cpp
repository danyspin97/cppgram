#include "cppgram/osutil.h"
#include "cppgram/exceptions.h"

int cppgram::osutil::backgroundProcess()
{
#ifdef __gnu_linux__
    //TODO
    return OSUTIL_NEWPROC_SUCCESS;
#else
    return OSUTIL_NEWPROC_NOTSUPPORTED;
#endif
}