#include "CoreBot.hpp"

using std::string;

using cppgram::CoreBot;
using cppgram::message;

bool
CoreBot::editMessageText(const string&   inline_message_id,
                         const string&   text,
                         const string&   reply_markup,
                         const ParseMode parse_mode,
                         const bool      disable_web_page_preview)
{
    string parseMode = "";

    if (parse_mode == ParseMode::HTML) {
        parseMode = "HTML";
    } else if (parse_mode == ParseMode::Markdown) {
        parseMode = "Markdown";
    }

    auto response = executeRequest(
            "editMessageText",
            cpr::Parameters{
                    {"inline_message_id", inline_message_id},
                    {"text", text},
                    {"parse_mode", parseMode},
                    {"disable_web_page_preview", disable_web_page_preview},
                    {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot)) {
        return false;
    }

    return valroot["result"].asBool();
}

bool
CoreBot::editMessageCaption(const string& inline_message_id,
                            const string& caption,
                            const string& reply_markup)
{
    auto response = executeRequest(
            "editMessageCaption",
            cpr::Parameters{{"inline_message_id", inline_message_id},
                            {"caption", caption},
                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot)) {
        return false;
    }

    return valroot["result"].asBool();
}

bool
CoreBot::editMessageReplyMarkup(const string& inline_message_id,
                                const string& reply_markup)
{
    int cpu_id = sched_getcpu();

    auto response = executeRequest(
            "editMessageReplyMarkup",
            cpr::Parameters{{"inline_message_id", inline_message_id},
                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot)) {
        return false;
    }

    return valroot["result"].asBool();
}
