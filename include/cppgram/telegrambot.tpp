#include <cpr/cpr.h>
#include <json/json.h>

#include "defines.h"
#include "telegrambot.h"
#include "cppgram/types/integers.h"
#include "singleton.h"
#include "utils.h"

using std::string;
using std::to_string;

using cpr::Session;

using namespace cppgram;
using namespace cppgram::util;


template<typename T>
uid_32 TelegramBot::sendMessage(const T &chat_id,
                                const std::string &text,
                                const string &reply_markup,
                                const ParseMode &parse_mode,
                                const bool &disable_web_page_preview,
                                const bool &disable_notification,
                                const uid_32 &reply_to_message_id) const
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

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + bot_token + "/sendMessage"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"chat_id", string_id},
                                                    {"text", text},
                                                    {"parse_mode", parseMode},
                                                    {"disable_web_page_preview",
                                                     to_string(disable_web_page_preview)},
                                                    {"disable_notification",
                                                     to_string(disable_notification)},
                                                    {"reply_to_message_id",
                                                     to_string(reply_to_message_id)},
                                                    {"reply_markup", reply_markup}});
    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 TelegramBot::editMessageText(const T &chat_id,
                                    const uid_32 &message_id,
                                    const string &text,
                                    const string &reply_markup,
                                    const ParseMode &parse_mode,
                                    const bool &disable_web_page_preview) const
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

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageText"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"chat_id", string_id},
                                                    {"message_id", to_string(message_id)},
                                                    {"text", text},
                                                    {"parse_mode", parseMode},
                                                    {"disable_web_page_preview",
                                                     to_string(disable_web_page_preview)},
                                                    {"reply_markup", reply_markup}});

    const cpr::Response response = sessions[cpu_id]->Get();
    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 TelegramBot::editMessageReplyMarkup(const T &chat_id,
                                           const uid_32 &message_id,
                                           const string &reply_markup) const
{
    string string_id;
    if (typeid(chat_id) == typeid(string_id))
        string_id = chat_id;
    else
        string_id = to_string(chat_id);

    int cpu_id = sched_getcpu();

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageReplyMarkup"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"chat_id", string_id},
                                                    {"message_id", to_string(message_id)},
                                                    {"reply_markup", reply_markup}});

    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 TelegramBot::editMessageCaption(const T &chat_id,
                                       const uid_32 &message_id,
                                       const string &caption,
                                       const string &reply_markup) const
{
    string string_id;
    if (typeid(chat_id) == typeid(string_id))
        string_id = chat_id;
    else
        string_id = to_string(chat_id);

    int cpu_id = sched_getcpu();

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageCaption"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"chat_id", string_id},
                    {"message_id", to_string(message_id)},
                    {"caption", caption},
                    {"reply_markup", reply_markup}});

    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

