#include<json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;

Singleton* Singleton::instance = nullptr;

Singleton::Singleton() : reader(new Json::Reader), writer(new Json::FastWriter), bot_token("")
{
    writer->omitEndingLineFeed();
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

Json::Reader* Singleton::getReader() const
{
    return this->reader;
}

Json::FastWriter* Singleton::getWriter() const
{
    return this->writer;
}

const std::string& Singleton::getLogFilename() const
{
    return logfilename;
}


