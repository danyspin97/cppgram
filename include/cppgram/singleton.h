#ifndef CPPGRAM_SINGLETON_H
#define CPPGRAM_SINGLETON_H

#include "parameters.h"

class Singleton
{
    public:
    static Singleton* Istance();

    static std::string& write(Json::Value& val);

    static inline Json::Reader* getReader() { return reader; };

    static inline Json::FastWriter* getWriter() { return writer; };

    private:
    Json::Reader* reader;
    Json::FastWriter* writer;
    class InlineKeyboard* Keyboards[THREADS];
};

#endif //CPPGRAM_SINGLETON_H
