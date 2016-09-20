#include <cpr/cpr.h>
#include <json/json.h>
#include "cppgram/editbot.h"
#include "cppgram/defines.h"
#include "cppgram/singleton.h"
#include "cppgram/structures.h"

using namespace cppgram;
using std::to_string;
using std::string;

uid_32 EditBot::editMessageText(const string& inline_message_id,
                              const string& text,
                              const string& reply_markup,
                              const ParseMode parse_mode,
                              const bool disable_web_page_preview) const
{
    string parseMode = "";

    if (parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";

    const cpr::Response
            response = cpr::Get(cpr::Url{TELEGRAMAPI + Singleton::getInstance()->getToken() + "/editMessageText"},
                                cpr::Parameters{{"inline_message_id", inline_message_id},
                                                {"text", text},
                                                {"parse_mode", parseMode},
                                                {"disable_web_page_preview", disable_web_page_preview},
                                                {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!Singleton::getInstance()->checkMethodError(response, valroot))
        return 1;

    return valroot["result"].asBool();
}
