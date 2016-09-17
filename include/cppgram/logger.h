#ifndef __CPPGRAM_LOGGER_H
#define __CPPGRAM_LOGGER_H

#include <string>

namespace cppgram
{
    
class Logger
{
public:
    explicit Logger(const std::string& filename);
    void log_event(const std::string& message) const;
    void log_error(const std::string& message) const;
    void log_warn(const std::string& message) const;
private:
    const std::string fname;
    std::string __getTime(const std::string& timeformat="%a %F %r") const;
};

}

#endif
