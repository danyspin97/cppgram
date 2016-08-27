#ifndef __CPPGRAM_LOGGER_H
#define __CPPGRAM_LOGGER_H

#include<string>
#include<fstream>

namespace cppgram
{
    class Logger
    {
    public:
        Logger(const std::ofstream& data_stream);
        void log_event(const std::string& message);
        void log_error(const std::string& message);
        void log_warn(const std::string& message);
    private:
        const std::ofstream stream;
    };
}

#endif