#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#define TELEGRAMAPI "https://api.telegram.org/bot"

#include <string>

//forward Json::Value
namespace Json
{
class Value;
class Reader;
class FastWriter;
}

namespace cpr
{
class Response;
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
                       const Json::Value& reply_markup,
                       ParseMode parse_mode = static_cast<ParseMode>(0),
                       bool disable_web_page_preview = true,
                       bool disable_notification = false,
                       uid_32 reply_to_message_id = 0);

    uid_32 sendMessage(const std::string& text,
                       ParseMode parse_mode = static_cast<ParseMode>(0),
                       bool disable_web_page_preview = true,
                       bool disable_notification = false,
                       uid_32 reply_to_message_id = 0);

    void editMessageText(uid_32 message_id, std::string& text);

    // Check if the called api method had any error, including connection(curl) error or api error returned by telegram
    bool checkMethodError(const cpr::Response& response, Json::Value& val);
private:
    const std::string bot_token, bot_usern;
    uid_32 updateId;
    std::string chatId, inlineQueryId, callbackQueryId;
    const uid_32 timeout, msg_limit;
    void getUpdates();
    void processUpdate(Json::Value &val);
    Json::Reader *reader;
    Json::FastWriter* writer;
};
    
}

#endif
