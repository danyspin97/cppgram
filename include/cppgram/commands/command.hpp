#ifndef COMMAND_HPP
#define COMMAND_HPP

#include <stdlib.h>
#include <string>

namespace cppgram
{
class Command
{
    public:
    std::string command;

    uint_fast8_t length;

    Command(){};

    Command( std::string command )
        : command( command )
        , length( command.size() )
    {
    }
};
}

#endif // COMMAND_H
