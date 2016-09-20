#include <iostream>
#include <json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;
using namespace std;

class EchoBot : public TelegramBot
{
    public:
    EchoBot(string token) : TelegramBot(token) {}
    void processMessage(const cppgram::message& message)
    {
        sendMessage(message.chat->id, message.text);
    }

};

int main() {
    MyBot bot(string("token"));
    bot.run();

    return 0;
}
