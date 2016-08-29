#include "cppgram/exceptions.h"

const char* cppgram::JsonParseError::what() const throw()
{
    return "Error while parsing JSON document";
}

const char* cppgram::NoHTTPOKResponse::what() const throw()
{
    return "HTTP Response status code is not 200/OK";
}

const char* cppgram::NotOkTelegramAPI::what() const throw()
{
    return "Telegram API's JSON says NOT OK!";
}