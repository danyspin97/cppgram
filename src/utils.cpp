#ifdef __unix__
#include<unistd.h>
#include<stdlib.h>
#endif

#include <sstream>
#include <fstream>
#include <mutex>

#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/utils.h"
#include "cppgram/singleton.h"
#include "cppgram/exceptions.h"

using cppgram::Singleton;
using cppgram::JsonParseError;

std::mutex mtx;
cpr::Session session;
Json::Reader* reader = Singleton::getInstance()->getReader();

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

    if(setsid() < 0)
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

const std::vector<std::string> cppgram::util::split(const std::string& str, const char& splchr)
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


const std::string cppgram::util::getTime(const std::string& timeformat)
{
    char finalTime[256];
    
    time_t ttime;
    struct tm *tinfo;

    ttime = time(NULL);
    tinfo = localtime(&ttime);
    
    if(tinfo==NULL) {
        return "tm error!";
    }
    
    if(strftime(finalTime,sizeof(finalTime),timeformat.c_str(),tinfo) == 0) {
        return "stfrtime() error!";
    }
    
    return std::string(finalTime);
}

void cppgram::util::log(const Log& l, const std::string& message, const std::string& filename) 
{
    std::string logType, fname;
    
    (filename == FILENAME_DEFAULT) ? fname=Singleton::getInstance()->getLogFilename() : fname=filename;
    
    if(l == Log::Error) 
        logType="[ERROR]";
    else if(l == Log::Event)
        logType="[EVENT]";
    else if(l == Log::Warning)
        logType="[WARNING]";
    
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    const std::string fmtStr = logType+"["+getTime()+"] "+message+'\n';
    out.write(fmtStr.c_str(),fmtStr.length());
    out.close();
}

const cpr::Response cppgram::util::request(const cpr::Url & url, const cpr::Parameters & params)
{
    mtx.lock();
    session.SetUrl(url);
    session.SetParameters(params);
    const cpr::Response r = session.Get();
    mtx.unlock();

    return r;
}

bool cppgram::util::checkMethodError(const cpr::Response &response, Json::Value &val)
{
    // If there was an error in the connection print it
    if (response.error.code != cpr::ErrorCode::OK) {
        log(Log::Error, "HTTP Error:" + response.error.message);
        return false;
    }

    mtx.lock();
    if (!reader->parse(response.text, val)) {
        log(Log::Error, "JSON Parser: Error while parsing JSON document!");
        throw new JsonParseError;
    }
    mtx.unlock();

    // Print method error
    if (response.status_code != 200) {
        log(Log::Error,
            "Telegram Error: " + val["error_code"].asString() + ", Description: " + val["description"].asString());
        return false;
    }

    return true;
}
