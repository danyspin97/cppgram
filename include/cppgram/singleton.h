#ifndef CPPGRAM_SINGLETON_H
#define CPPGRAM_SINGLETON_H

#include <string>

namespace Json
{
class Reader;
class FastWriter;
class Value;
}

namespace cpr
{
class Response;
}

namespace cppgram
{

class Singleton
{
public:
    Singleton(const Singleton &prev) = delete;
    ~Singleton();
    static Singleton *getInstance();
    Json::Reader *getReader() const;
    Json::FastWriter *getWriter() const;
    const std::string &getLogFilename() const;
    void setLogFilename(const std::string &new_filename);

private:
    Singleton();
    static Singleton *instance;
    Json::Reader *reader;
    Json::FastWriter *writer;
    std::string logfilename;
};

}

#endif //CPPGRAM_SINGLETON_H
