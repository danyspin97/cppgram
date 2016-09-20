#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include <string>

namespace Json
{
class Value;
class Reader;
}

namespace cpr
{
class Response;
}

namespace cppgram
{

//forwards
enum ParseMode : short;
typedef unsigned long uid_32;
typedef long long id_64;

class TelegramBot
{
    public:
    TelegramBot(const std::string &api_token,
                const std::string &botusern,
                const bool &background = false,
                const std::string &filename = "tgbot.log",
                const uid_32 &message_limit = 100,
                const uid_32 &timeout = 60);
    void run();
    protected:
//basic bot core functions
    virtual void processMessage(const struct message &message);
    virtual void processEditedMessage(const struct message &editedMessage);
    virtual void processInlineQuery(const struct inlineQuery &inlineQuery);
    virtual void processChosenInlineResult(const struct choosenInlineResult &choosenInlineResult);
    virtual void processCallbackQuery(const struct callbackQuery &callbackQuery);

    template<typename T>
    uid_32 sendMessage(const T &id,
                       const std::string &text,
                       const std::string &reply_markup = "",
                       const ParseMode &parse_mode = static_cast<ParseMode>(1),
                       const bool &disable_web_page_preview = true,
                       const bool &disable_notification = false,
                       const uid_32 &reply_to_message_id = 0) const;

    template<typename T>
    uid_32 editMessageText(const T &id,
                           const uid_32 &message_id,
                           const std::string &text,
                           const std::string &reply_markup = "",
                           const ParseMode parse_mode = static_cast<ParseMode>(1),
                           const bool disable_web_page_preview = true) const;

    bool editMessageText(const std::string &inline_message_id,
                         const std::string &text,
                         const std::string &reply_markup = "",
                         const ParseMode parse_mode = static_cast<ParseMode>(1),
                         const bool disable_web_page_preview = true) const;

    bool answerInlineQuery(const std::string &inline_query_id,
                           const std::string &results,
                           const int &cache_time = 300,
                           const bool &is_personal = false,
                           const std::string &next_offset = "",
                           const std::string &switch_pm_text = "",
                           const std::string &switch_pm_paramter = "");
    void getUpdates();

    private:
    const std::string bot_token, bot_usern;
    uid_32 updateId;
    const uid_32 timeout, msg_limit;
    void processUpdate(Json::Value &val);
    bool checkMethodError(const cpr::Response& response, Json::Value& val) const;
    Json::Reader* reader;
};

}

#include "telegrambot.tpp"

#endif
