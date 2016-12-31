#include <cpr/cpr.h>
#include <json/json.h>

#include "telegrambot.h"
#include "types/enums.h"
#include "defines.h"
#include "utils.h"

using std::string;
using std::to_string;

using cpr::Session;

using cppgram::ParseMode;
using cppgram::TelegramBot;

template<typename T>
int_fast32_t TelegramBot::sendMessage(const T &chat_id,
                                const std::string &text,
                                const string &reply_markup,
                                const ParseMode &parse_mode,
                                const bool &disable_web_page_preview,
                                const bool &disable_notification,
                                const int_fast32_t &reply_to_message_id)
{
    string parseMode = "", string_id;

    if (typeid(chat_id) == typeid(string_id))
        string_id = chat_id;
    else
        string_id = to_string(chat_id);

    if (parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";

    int cpu_id = sched_getcpu();

    _sessions[cpu_id].SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/sendMessage"});
    _sessions[cpu_id].SetParameters(cpr::Parameters{{"chat_id", string_id},
                                                    {"text", text},
                                                    {"parse_mode", parseMode},
                                                    {"disable_web_page_preview",
                                                     to_string(disable_web_page_preview)},
                                                    {"disable_notification",
                                                     to_string(disable_notification)},
                                                    {"reply_to_message_id",
                                                     to_string(reply_to_message_id)},
                                                    {"reply_markup", reply_markup}});
    const cpr::Response response = _sessions[cpu_id].Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
    {
        return 1;
    }

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
int_fast32_t TelegramBot::editMessageText(const T &chat_id,
                                    const int_fast32_t &message_id,
                                    const string &text,
                                    const string &reply_markup,
                                    const ParseMode &parse_mode,
                                    const bool &disable_web_page_preview)
{
    string parseMode = "", string_id;

    if (typeid(chat_id) == typeid(string_id))
        string_id = chat_id;
    else
        string_id = to_string(chat_id);

    if (parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";

    int cpu_id = sched_getcpu();

    _sessions[cpu_id].SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/editMessageText"});
    _sessions[cpu_id].SetParameters(cpr::Parameters{{"chat_id", string_id},
                                                    {"message_id", to_string(message_id)},
                                                    {"text", text},
                                                    {"parse_mode", parseMode},
                                                    {"disable_web_page_preview",
                                                     to_string(disable_web_page_preview)},
                                                    {"reply_markup", reply_markup}});

    const cpr::Response response = _sessions[cpu_id].Get();
    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
int_fast32_t TelegramBot::editMessageReplyMarkup(const T &chat_id,
                                           const int_fast32_t &message_id,
                                           const string &reply_markup)
{
    string string_id;
    if (typeid(chat_id) == typeid(string_id))
        string_id = chat_id;
    else
        string_id = to_string(chat_id);

    int cpu_id = sched_getcpu();

    _sessions[cpu_id].SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/editMessageReplyMarkup"});
    _sessions[cpu_id].SetParameters(cpr::Parameters{{"chat_id", string_id},
                                                    {"message_id", to_string(message_id)},
                                                    {"reply_markup", reply_markup}});

    const cpr::Response response = _sessions[cpu_id].Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
int_fast32_t TelegramBot::editMessageCaption(const T &chat_id,
                                       const int_fast32_t &message_id,
                                       const string &caption,
                                       const string &reply_markup)
{
    string string_id;
    if (typeid(chat_id) == typeid(string_id))
        string_id = chat_id;
    else
        string_id = to_string(chat_id);

    int cpu_id = sched_getcpu();

    _sessions[cpu_id].SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/editMessageCaption"});
    _sessions[cpu_id].SetParameters(cpr::Parameters{{"chat_id", string_id},
                    {"message_id", to_string(message_id)},
                    {"caption", caption},
                    {"reply_markup", reply_markup}});

    const cpr::Response response = _sessions[cpu_id].Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

