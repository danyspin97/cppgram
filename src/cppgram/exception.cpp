// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "cppgram/exception.hpp"

using namespace cppgram;

const char *
ThreadException::what() const throw()
{
    return "Thread could not started correctly";
}

const char *
JsonParseError::what() const throw()
{
    return "Error while parsing JSON document";
}

const char *
InlineKeyboardNotValid::what() const throw()
{
    return "Inline keyboard contains data not valid";
}
