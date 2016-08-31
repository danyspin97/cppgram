#ifndef __CPPGRAM_LOGGER_H
#define __CPPGRAM_LOGGER_H

#include <string>

namespace cppgram
{
    class Logger
    {
    public:
        Logger(const char* filename);
        void log_event(const char* message) const;
        void log_error(const char* message) const;
        void log_warn(const char* message) const;
    private:
        const char* fname;
        std::string __getTime() const;
    };
}

#endif
