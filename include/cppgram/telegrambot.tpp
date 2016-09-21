#include <cpr/cpr.h>
#include <json/json.h>

#include "defines.h"
#include "telegrambot.h"
#include "types.h"
#include "singleton.h"
#include "structures.h"

using namespace cppgram;

using std::string;
using std::to_string;

template<typename T>
uid_32 TelegramBot::sendMessage(const T &id, const std::string &text,
                                const string &reply_markup,
                                const ParseMode &parse_mode,
                                const bool &disable_web_page_preview,
                                const bool &disable_notification,
                                const uid_32 &reply_to_message_id) const
{
    string parseMode = "", fid;

    if (typeid(id) == typeid(fid))
        fid = id;
    else
        fid = to_string(id);

    if (parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";

    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/sendMessage"},
                                            cpr::Parameters{{"chat_id", fid},
                                                            {"text", text},
                                                            {"parse_mode", parseMode},
                                                            {"disable_web_page_preview",
                                                             to_string(disable_web_page_preview)},
                                                            {"disable_notification", to_string(disable_notification)},
                                                            {"reply_to_message_id", to_string(reply_to_message_id)},
                                                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 TelegramBot::editMessageText(const T &id,
                                    const uid_32 &message_id,
                                    const string &text,
                                    const string &reply_markup,
                                    const ParseMode &parse_mode,
                                    const bool &disable_web_page_preview) const
{
    string parseMode = "", fid;

    if (typeid(id) == typeid(fid))
        fid = id;
    else
        fid = to_string(id);

    if (parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";

    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageText"},
                                            cpr::Parameters{{"chat_id", fid},
                                                            {"message_id", to_string(message_id)},
                                                            {"text", text},
                                                            {"parse_mode", parseMode},
                                                            {"disable_web_page_preview",
                                                             to_string(disable_web_page_preview)},
                                                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 TelegramBot::editMessageReplyMarkup(const T &id,
                                           const uid_32 &message_id,
                                           const string &reply_markup) const
{
    string fid;
    if (typeid(id) == typeid(fid))
        fid = id;
    else
        fid = to_string(id);

    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageReplyMarkup"},
                                            cpr::Parameters{{"chat_id", fid},
                                                            {"message_id", to_string(message_id)},
                                                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 TelegramBot::editMessageCaption(const T &id,
                                       const uid_32 &message_id,
                                       const string &caption,
                                       const string &reply_markup) const
{
    string fid;
    if (typeid(id) == typeid(fid))
        fid = id;
    else
        fid = to_string(id);

    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageCaption"},
                                            cpr::Parameters{{"chat_id", fid},
                                                            {"message_id", to_string(message_id)},
                                                            {"caption", caption},
                                                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}
