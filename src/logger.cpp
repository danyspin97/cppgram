#include<time.h>

#include "cppgram/logger.h"

cppgram::Logger::Logger(std::ostream& data_stream)
    : stream(&data_stream)
{

}

void cppgram::Logger::log_error(const char* message) const
{
    std::string fmtStr = "[ERROR][";
    fmtStr.append(__getTime());
    fmtStr.append("] ");
    fmtStr.append(message);
    fmtStr.append("\n");

    (*stream) << fmtStr;
}

void cppgram::Logger::log_event(const char* message) const
{
    std::string fmtStr = "[EVENT][";
    fmtStr.append(__getTime());
    fmtStr.append("] ");
    fmtStr.append(message);
    fmtStr.append("\n");

    (*stream) << fmtStr;
}

void cppgram::Logger::log_warn(const char* message) const
{
    std::string fmtStr = "[WARNING][";
    fmtStr.append(__getTime());
    fmtStr.append("] ");
    fmtStr.append(message);
    fmtStr.append("\n");


    (*stream) << fmtStr;
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
