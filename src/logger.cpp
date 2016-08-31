#include<time.h>
#include<fstream>

#include "cppgram/logger.h"

cppgram::Logger::Logger(const char* filename) : fname(filename)
{

}

void cppgram::Logger::log_error(const char* message) const
{
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    std::string fmtStr = "[ERROR][";
    fmtStr.append(__getTime());
    fmtStr.append("] ");
    fmtStr.append(message);
    fmtStr.append("\n");
    out.write(fmtStr.c_str(),fmtStr.length());
    out.close();
}

void cppgram::Logger::log_event(const char* message) const
{
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    std::string fmtStr = "[EVENT][";
    fmtStr.append(__getTime());
    fmtStr.append("] ");
    fmtStr.append(message);
    fmtStr.append("\n");
    out.write(fmtStr.c_str(),fmtStr.length());
    out.close();
}

void cppgram::Logger::log_warn(const char* message) const
{
    std::ofstream out;
    out.open(fname, std::ios::app | std::ios::out);
    std::string fmtStr = "[WARNING][";
    fmtStr.append(__getTime());
    fmtStr.append("] ");
    fmtStr.append(message);
    fmtStr.append("\n");
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
