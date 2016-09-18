#include<json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;

Singleton* Singleton::instance = nullptr;

Singleton::Singleton() : reader(new Json::Reader), writer(new Json::FastWriter)
{
    writer->omitEndingLineFeed();
    for (int i = THREADS - 1; i--; ) {
        keyboards[i] = new InlineKeyboard();
    }
}

Singleton::~Singleton()
{
    delete reader;
    delete writer;
    
    if(instance != NULL) {
        delete instance;
    }
}

Singleton* Singleton::getInstance()
{
    if(instance == NULL) {
        instance = new Singleton;
    }
    
    return instance;
}

std::string Singleton::write(Json::Value& val)
{
     return writer->write(val);
}

Json::Reader* Singleton::getReader()
{
    return this->reader;
}

Json::FastWriter* Singleton::getWriter()
{
    return this->writer;
}
