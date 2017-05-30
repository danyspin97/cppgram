#ifndef CPPGRAM_UTILITIES_HPP
#define CPPGRAM_UTILITIES_HPP

#include <string>

namespace cppgram
{
namespace utilities
{
template <typename T>
std::string
str( T t )
{
    return std::to_string( t );
}

template <>
std::string
str<std::string>( std::string t )
{
    return t;
}

template <>
std::string
str<const char *>( const char *t )
{
    return std::string{t};
}
}
}
#endif
