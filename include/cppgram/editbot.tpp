#include <cpr/cpr.h>
#include <json/json.h>
#include <string>

#include "cppgram/editbot.h"
#include "cppgram/singleton.h"
#include "cppgram/structures.h"

using namespace cppgram;

using std::string;
using std::to_string;

template<typename T>
uid_32 EditBot::editMessageText(const T &id,
                                const uid_32 &message_id,
                                const std::string &text,
                                const string &reply_markup,
                                const ParseMode parse_mode,
                                const bool disable_web_page_preview) const
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

    const cpr::Response
            response = cpr::Get(cpr::Url{TELEGRAMAPI + Singleton::getInstance()->getToken() + "/editMessageText"},
                                cpr::Parameters{{"chat_id", fid},
                                                {"message_id", to_string(message_id)},
                                                {"text", text},
                                                {"parse_mode", parseMode},
                                                {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                                {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!Singleton::getInstance()->checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}
