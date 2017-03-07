#include "CoreBot.hpp"

using std::string;
using std::to_string;

using cppgram::CoreBot;
using cppgram::message;
using cppgram::ParseMode;

template <typename T>
message
CoreBot::editMessageText(const T&           chat_id,
                         const int_fast32_t message_id,
                         const string&      text,
                         const string&      reply_markup,
                         const ParseMode    parse_mode,
                         const bool         disable_web_page_preview)
{
    string parseMode = "", string_id;

    if (typeid(chat_id) == typeid(string_id)) {
        string_id = chat_id;
    } else {
        string_id = to_string(chat_id);
    }

    if (parse_mode == ParseMode::HTML) {
        parseMode = "HTML";
    } else if (parse_mode == ParseMode::Markdown) {
        parseMode = "Markdown";
    }

    auto response = executeRequest(
            "editMessageText",
            cpr::Parameters{{"chat_id", string_id},
                            {"message_id", to_string(message_id)},
                            {"text", text},
                            {"parse_mode", parseMode},
                            {"disable_web_page_preview",
                             to_string(disable_web_page_preview)},
                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot)) {
        return message();
    }

    return message(valroot["result"]);
}

template <typename T>
message
CoreBot::editMessageReplyMarkup(const T&            chat_id,
                             const int_fast32_t message_id,
                             const string&       reply_markup)
{
    string string_id;
    if (typeid(chat_id) == typeid(string_id)) {
        string_id = chat_id;
    }
    else {
        string_id = to_string(chat_id);
    }

    auto response = executeRequest("editMessageReplyMarkup",
            cpr::Parameters{{"chat_id", string_id},
                            {"message_id", to_string(message_id)},
                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return message();

    return message(valroot["result"]);
}

template <typename T>
message
CoreBot::editMessageCaption(const T&            chat_id,
                                const int_fast32_t message_id,
                                const string&       caption,
                                const string&       reply_markup)
{
    string string_id;
    if (typeid(chat_id) == typeid(string_id)) {
        string_id = chat_id;
}
    else {
        string_id = to_string(chat_id);
    }

    auto response = executeRequest("editMessageCaption", cpr::Parameters{{"chat_id", string_id},
                            {"message_id", to_string(message_id)},
                            {"caption", caption},
                            {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return message();

    return message(valroot["result"]);
}
