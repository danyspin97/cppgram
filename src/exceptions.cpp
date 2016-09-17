#include "cppgram/exceptions.h"

using namespace cppgram;

const char* JsonParseError::what() const throw()
{
    return "Error while parsing JSON document";
}

const char* NotOkTelegramAPI::what() const throw()
{
    return "Telegram API's JSON says NOT OK!";
}

const char* BgProcessOSNotSupported::what() const throw()
{
    return "Operating System's new background process implementation not supported";
}

const char* BgProcessFailed::what() const throw()
{
    return "Error while creating new process";
}

const char* InlineKeyboardNotValid::what() const throw()
{
    return "Inline keyboard contains data not valid";
}
