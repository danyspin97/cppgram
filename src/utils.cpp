#ifdef __unix__
#include <unistd.h>
#include <stdlib.h>
#endif

#include <sstream>
#include <fstream>

#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/utils.h"
#include "cppgram/exceptions.h"

using namespace cppgram;

Json::Reader reader;

int cppgram::osutil::backgroundProcess()
{
#ifdef __gnu_linux__
    pid_t procid;

    procid = fork();
    switch (procid) {
        case -1: return OSUTIL_NEWPROC_FAILED;
        case 0: break;
        default: exit(0);
    }

    if (setsid() < 0)
        return OSUTIL_NEWPROC_FAILED;

    /*close file descriptors*/
    close(0);
    close(1);
    close(2);

    return OSUTIL_NEWPROC_SUCCESS;
#else
    return OSUTIL_NEWPROC_NOTSUPPORTED;
#endif
}

const std::vector<std::string> cppgram::split(const std::string &str, const char &splchr)
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

const std::string cppgram::getTime(const std::string &timeformat)
{
    char finalTime[256];

    time_t ttime;
    struct tm *tinfo;

    ttime = time(NULL);
    tinfo = localtime(&ttime);

    if (tinfo == NULL) {
        return "tm error!";
    }

    if (strftime(finalTime, sizeof(finalTime), timeformat.c_str(), tinfo) == 0) {
        return "stfrtime() error!";
    }

    return std::string(finalTime);
}

void cppgram::log(const Log &logType, const std::string &message, const std::string &filename)
{
    std::string logTypeString;

    switch(logType)
    {
        case Error:
            logTypeString = "[ERROR]";
            break;
        case Event:
            logTypeString = "[EVENT]";
            break;
        case Warning:
            break;
            logTypeString = "[WARNING]";
    }

    // TODO Keep stream open
    std::ofstream out;
    out.open(filename, std::ios::app | std::ios::out);
    const std::string fmtStr = logTypeString + "[" + getTime() + "] " + message + '\n';
    out.write(fmtStr.c_str(), fmtStr.length());
    out.close();
}

bool cppgram::checkMethodError(const cpr::Response &response, Json::Value &val)
{
    // If there was an error in the connection print it
    if (response.error.code != cpr::ErrorCode::OK)
    {
        log(Log::Error, "HTTP Error:" + response.error.message);
        return false;
    }

    if (!reader.parse(response.text, val))
    {
        log(Log::Error, "JSON Parser: Error while parsing JSON document!");
        throw JsonParseError();
    }

    // Print method error
    if (response.status_code != 200)
    {
        log(Log::Error, "Telegram Error: " + val["error_code"].asString() + ", Description: " + val["description"].asString());
        return false;
    }

    return true;
}
