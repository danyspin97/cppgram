#ifndef __CPPGRAM_LOGGER_H
#define __CPPGRAM_LOGGER_H

#include <fstream>

namespace cppgram
{
    class Logger
    {
    public:
        Logger(std::ostream& data_stream);
        void log_event(const char* message) const;
        void log_error(const char* message) const;
        void log_warn(const char* message) const;
    private:
        std::ostream *stream;
        std::string __getTime() const;
    };
}

#endif