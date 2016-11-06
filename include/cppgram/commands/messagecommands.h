#ifndef MESSAGECOMMANDS_H
#define MESSAGECOMMANDS_H

#include "command.h"

namespace cppgram
{

typedef void (*MessageScript)(class TelegramBot*, const struct message*);

class MessageCommand : public Command
{
    public:

    MessageScript script;

    MessageCommand() { script = 0; }

    MessageCommand(std::string& command, MessageScript script)
        : Command("/" + command), script(script)
    {
    }

};

}

#endif // MESSAGECOMMANDS_H
