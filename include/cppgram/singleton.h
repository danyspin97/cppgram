#ifndef CPPGRAM_SINGLETON_H
#define CPPGRAM_SINGLETON_H

#include <string>

namespace Json
{
class Reader;
class FastWriter;
class Value;
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
    const std::string &getToken()
    { return bot_token; };
    void setToken(std::string &new_token)
    { bot_token = new_token; }
    private:
    Singleton();
    static Singleton *instance;
    Json::Reader *reader;
    Json::FastWriter *writer;
    std::string bot_token;
};

}

#endif //CPPGRAM_SINGLETON_H
