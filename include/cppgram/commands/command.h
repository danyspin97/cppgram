#ifndef COMMAND_H
#define COMMAND_H

#include <string>
#include <stdlib.h>

namespace cppgram
{

class Command
{
    public:

    std::string command;

    uint_fast8_t length;

    Command() {};

    Command(std::string command)
        : command(command), length(command.size())
    {
    }

};

}

#endif // COMMAND_H
