#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#define TELEGRAMAPI "https://api.telegram.org/bot"
#define SENDMSG_DEFAULT_CHATID "default"

#include <string>
#include <cpr/cpr.h>

//forward Json::Value
namespace Json
{
class Value;
}

namespace cppgram
{

//forwards
class Logger;
enum ParseMode : short;
typedef unsigned long uid_32;

class CoreBot : public Logger
{
public:
    CoreBot(const std::string &api_token,
            bool background = false,
            const std::string filename="tgbot.log",
            int message_limit = 100,
            int timeout = 60
            );
    void run();
    void apiRequest(std::string& apiMethod, cpr::Parameters parameters) const;

protected:
    //basic bot core functions
    virtual void processMessage(const struct message& message);
    virtual void processEditedMessage(const struct message& editedMessage);
    virtual void processInlineQuery(const struct inlineQuery& inlineQuery);
    virtual void processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult);
    virtual void processCallbackQuery(const struct callbackQuery& callbackQuery);
    const struct message& sendMessage(const std::string& chat_id,
                     const std::string& text,
                     ParseMode parse_mode = static_cast<ParseMode>(1),
                     bool disable_web_page_preview = true,
                     bool disable_notification = false,
                     uid_32 reply_to_message_id = 0,
                     void* reply_markup = nullptr);
    //void editMessage
private:
    const std::string bot_token;
    uid_32 lastUpdateId, lastChatId;
    int timeout, msg_limit;
    void getUpdates();
    void processUpdate(Json::Value &val);
};
    
}

#endif
