#include<json/json.h>
#include "cppgram/singleton.h"

using namespace cppgram;

Singleton* Singleton::instance = nullptr;

Singleton::Singleton() : reader(new Json::Reader), writer(new Json::FastWriter)
{}

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
     return "";
}

Json::Reader* Singleton::getReader()
{
    return this->reader;
}

Json::FastWriter* Singleton::getWriter()
{
    return this->writer;
}
