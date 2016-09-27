#include<json/json.h>
#include<cpr/cpr.h>

#include "cppgram/defines.h"
#include "cppgram/singleton.h"
#include "cppgram/utils.h"
#include "cppgram/exceptions.h"

using namespace cppgram;
using util::Log;
using util::log;

Singleton* Singleton::instance = nullptr;

Singleton::Singleton() : reader(new Json::Reader), writer(new Json::FastWriter)
{
    writer->omitEndingLineFeed();
}

Singleton::~Singleton()
{
    delete reader;
    delete writer;
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

void Singleton::setLogFilename(const std::string &new_filename)
{
    logfilename = new_filename;
}


