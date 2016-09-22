#include <cppgram/cppgram.h>

#define TOKEN "token"

using namespace cppgram;

class EchoBot : public TelegramBot
{
    public:
    EchoBot(const std::string token) : TelegramBot("token") {}
    void processMessage(const cppgram::message& message) override final
    {
		 if(message.chat->type != ChatType::Private) 
			sendMessage(message.chat->id, "Message: *message.text*"+" sent by: *"+message.user->username+"*", ParseMode::Markdown);
       else
			sendMessage(message.chat->id, "Message: *message.text*", ParseMode::Markdown);
    }

};

int main() {
    MyBot bot(TOKEN);
    bot.run();

    return 0;
}
