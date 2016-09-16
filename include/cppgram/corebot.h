#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#define TELEGRAMAPI "https://api.telegram.org/bot"

#include <string>

//forward Json::Value
namespace Json
{
class Value;
class Reader;
}

namespace cppgram
{

//forwards
class Logger;
enum ParseMode : short;
typedef unsigned long uid_32;
typedef long long id_64;

class CoreBot : public Logger
{
public:
    CoreBot(const std::string &api_token,
            const std::string &botusern,
            const bool &background = false,
            const std::string &filename="tgbot.log",
            const uid_32 &message_limit = 100,
            const uid_32 &timeout = 60
            );
    ~CoreBot();
    void run();
protected:
    //basic bot core functions
    virtual void processMessage(const struct message& message);
    virtual void processEditedMessage(const struct message& editedMessage);
    virtual void processInlineQuery(const struct inlineQuery& inlineQuery);
    virtual void processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult);
    virtual void processCallbackQuery(const struct callbackQuery& callbackQuery);
    
    template<typename T>
    uid_32 sendMessage(const T& id,
                     const std::string& text,
                     const ParseMode& parse_mode = static_cast<ParseMode>(1),
                     const bool &disable_web_page_preview = true,
                     const bool &disable_notification = false,
                     const uid_32 &reply_to_message_id = 0,
                     const void* reply_markup = nullptr) const;
    uid_32 sendMessage(const std::string& text,
                     const ParseMode& parse_mode = static_cast<ParseMode>(1),
                     const bool &disable_web_page_preview = true,
                     const bool &disable_notification = false,
                     const uid_32 &reply_to_message_id = 0,
                     const void* reply_markup = nullptr) const;
    //void editMessage
    //void apiRequest(std::string& apiMethod, cpr::Parameters parameters) const;
private:
    const std::string bot_token, bot_usern;
    uid_32 updateId;
    id_64 chatId;
    const uid_32 timeout, msg_limit;
    void getUpdates();
    void processUpdate(Json::Value &val);
    Json::Reader *reader;
};
    
}

#endif
