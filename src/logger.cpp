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

std::string cppgram::Logger::__getTime() const
{
    time_t raw;
    struct tm *tinfo;

    time(&raw);
    tinfo = localtime(&raw);

    std::string fmtTime = asctime(tinfo);
    fmtTime.erase(fmtTime.size()-1);
    return fmtTime;
}
