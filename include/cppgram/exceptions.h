#ifndef __CPPGRAM_EXCEPTIONS_H
#define __CPPGRAM_EXCEPTIONS_H

#include<exception>

namespace cppgram
{
    class JsonParseError : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };

    class NoHTTPOKResponse : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };

    class NotOkTelegramAPI : public std::exception
    {
    public:
        virtual const char* what() const throw();
    };
}

#endif