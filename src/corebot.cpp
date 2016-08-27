#include "cppgram/corebot.h"
#include "cppgram/exceptions.h"

//using cppgram::JsonParseError;

cppgram::CoreBot::CoreBot(const std::string &api_token, const std::ofstream& output)
        : Logger(output), botok(api_token)
{

}

