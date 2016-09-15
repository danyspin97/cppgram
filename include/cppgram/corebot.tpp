#include <cpr/cpr.h>
#include <json/json.h>
#include <string>

#include "cppgram.h"

using std::string;
using std::to_string;

template<typename T>
void cppgram::CoreBot::sendMessage(const T& id, const string& text,  ParseMode parse_mode, bool disable_web_page_preview, bool disable_notification, cppgram::uid_32 reply_to_message_id, void* reply_markup)
{
    string fid, parseMode="HTML";
    if(typeid(id) != typeid(fid)) 
        fid=to_string(id);
    else
        fid=id;

    if(parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if(parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";
    
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/sendMessage"},
                  cpr::Parameters{{"chat_id", fid}, {"text", text},
                                  {"parse_mode", parseMode},
                                  {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                  {"disable_notification", to_string(disable_notification)},
                                  {"reply_to_message_id", to_string(reply_to_message_id)}});
                                  //{"reply_markup", reply_markup}});*/

    if(response.status_code != 200) {
        log_warn("(sendMessage) HTTP Response status code is not 200: "+to_string(response.status_code));
    } else {
        string json_doc = response.text;
        Json::Value valroot;
        Json::Reader reader;

        if(!reader.parse(json_doc.c_str(),valroot)) {
            log_error("(sendMessage) Error while parsing JSON document!");
            throw new JsonParseError;
        }

        log_event("Sent message to chatId/@usernchan: "+fid+", text: "+text+", parse mode: "+parseMode);
    }
}
