#include <cpr/cpr.h>
#include <json/json.h>
#include <string>

#include "corebot.h"
#include "types.h"

using namespace cppgram;

using std::string;
using std::to_string;

template<typename T>
uid_32 cppgram::CoreBot::sendMessage(const T& id, const string& text,  const ParseMode& parse_mode, const bool& disable_web_page_preview, const bool& disable_notification, const uid_32& reply_to_message_id, const void* reply_markup) const
{
    string fid, parseMode;
    cpr::Parameters httpGETparams;
    
    if(typeid(id) != typeid(fid)) 
        fid=to_string(id);
    else
        fid=id;

    if(parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if(parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";
    
    if(parse_mode == ParseMode::None) { 
        httpGETparams = {{"chat_id", chatId}, {"text", text},
                                    {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                    {"disable_notification", to_string(disable_notification)},
                                    {"reply_to_message_id", to_string(reply_to_message_id)}};
    } else {
        httpGETparams = {{"chat_id", chatId}, {"text", text},
                                    {"parse_mode",parseMode},
                                    {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                    {"disable_notification", to_string(disable_notification)},
                                    {"reply_to_message_id", to_string(reply_to_message_id)}};
    }
    
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/sendMessage"},httpGETparams);
                                  //{"reply_markup", reply_markup}});*/

    Json::Value valroot;

    // If there was an error in the connection print it
    if (response.error.code != cpr::ErrorCode::OK) {
        log_error("Error:" + response.error.message);
        return 1;
    }

    if(!reader->parse(response.text,valroot)) {
        log_error("(sendMessage) Error while parsing JSON document!");
        return 1;
    }

    // Print method error
    if(response.status_code != 200) {
        log_error("Error code: " + valroot["error_code"].asString() + "/n Description: " + valroot["description"].asString());
        return 1;
    }

    return valroot["result"]["message_id"].asUInt();
}
