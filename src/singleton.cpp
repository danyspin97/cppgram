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

const std::string& Singleton::getToken() const
{
    return bot_token;
}

void Singleton::setLogFilename(const std::string &new_filename)
{
    logfilename = new_filename;
}

short Singleton::setToken(const std::string &new_token)
{
    if(!bot_token.empty()) {
        bot_token = new_token;
        return 0;
    } else
        return BOT_TOKEN_ALREADY_DEFINED;
}

bool Singleton::checkMethodError(const cpr::Response& response, Json::Value& val) const
{
    // If there was an error in the connection print it
    if (response.error.code != cpr::ErrorCode::OK) {
        log(Log::Error,"HTTP Error:" + response.error.message);
        return false;
    }

    if(!Singleton::getInstance()->getReader()->parse(response.text, val)) {
        log(Log::Error,"JSON Parser: Error while parsing JSON document!");
        throw new JsonParseError;
    }

    // Print method error
    if(response.status_code != 200) {
        log(Log::Error,"Telegram Error: " + val["error_code"].asString() + ", Description: " + val["description"].asString());
        return false;
    }

    return true;
}


