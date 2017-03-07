#include "CoreBot.hpp"

using std::to_string;

using cppgram::CoreBot;
using cppgram::message;
using cppgram::ParseMode;

message
CoreBot::sendMessage(const std::string&       text,
                           const std::string&       reply_markup,
                           const ParseMode parse_mode,
                           const bool               disable_web_page_preview,
                           const bool               disable_notification,
                           const int_fast32_t       reply_to_message_id)
{
    std::string parseMode = "";

    if (parse_mode == ParseMode::HTML) {
        parseMode = "HTML";
    } else if (parse_mode == ParseMode::Markdown) {
        parseMode = "Markdown";
    }

    auto response = executeRequest(
            "sendMessage",
            cpr::Parameters{
                    {"chat_id", _chat_id},
                    {"text", text},
                    {"parse_mode", parseMode},
                    {"disable_web_page_preview",
                     to_string(disable_web_page_preview)},
                    {"disable_notification", to_string(disable_notification)},
                    {"reply_to_message_id", to_string(reply_to_message_id)},
                    {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot)) {
        return message();
    }

    return message(valroot["result"]);
}
