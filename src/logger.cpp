#include<time.h>
#include<fstream>

#include "cppgram/logger.h"

cppgram::Logger::Logger(const std::string& filename) : fname(filename)
{

}

void cppgram::Logger::log_error(const std::string& message) const
{
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    const std::string fmtStr = "[ERROR]["+__getTime()+"] "+message+'\n';
    out.write(fmtStr.c_str(),fmtStr.length());
    out.close();
}

void cppgram::Logger::log_event(const std::string& message) const
{
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    const std::string fmtStr = "[EVENT]["+__getTime()+"] "+message+'\n';
    out.write(fmtStr.c_str(),fmtStr.length());
    out.close();
}

void cppgram::Logger::log_warn(const std::string& message) const
{
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    const std::string fmtStr = "[WARNING]["+__getTime()+"] "+message+'\n';
    out.write(fmtStr.c_str(),fmtStr.length());
    out.close();
}

std::string cppgram::Logger::__getTime(const std::string& timeformat) const
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
