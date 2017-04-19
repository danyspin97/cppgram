#include <cppgram/cppgram.h>

#define TOKEN "token"

using namespace cppgram;

class EchoBot : public TelegramBot
{
    public:
    EchoBot() : TelegramBot(TOKEN) {}
    void processMessage(const struct message& message) override final
    {
		 if(message.chat->type != EChatType::Private)
			sendMessage(message.chat->id, "Message: *"+message.text+"* sent by: *"+message.from->username+"*","" ,EParseMode::Markdown);
       else
			sendMessage(message.chat->id, "Message: *"+message.text+"*", "",ParseMode::Markdown);
    }

};

int main() {
    EchoBot bot;
    bot.run();

    return 0;
}
