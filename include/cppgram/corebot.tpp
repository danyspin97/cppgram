#include <cpr/cpr.h>
#include <json/json.h>
#include <string>

#include "corebot.h"
#include "types.h"

using namespace cppgram;

using std::string;
using std::to_string;

template<typename T>
uid_32 cppgram::CoreBot::sendMessage(const T& id, const string& text,  const ParseMode& parse_mode, 
                                     const bool& disable_web_page_preview, const bool& disable_notification, 
                                     const uid_32& reply_to_message_id) const
{
    string fid, parseMode="";
    
    if(typeid(id) != typeid(fid)) 
        fid=to_string(id);
    else
        fid=id;

    if(parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if(parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";
    
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/sendMessage"},
                                            cpr::Parameters{{"chat_id",to_string(chatId)}, {"text", text},
                                  {"parse_mode", parseMode},
                                  {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                  {"disable_notification", to_string(disable_notification)},
                                  {"reply_to_message_id", to_string(reply_to_message_id)}});

    Json::Value valroot;
    
    if (!checkMethodError(response, valroot))
        return 1;
    
    return valroot["result"]["message_id"].asUInt();
}

template<typename T>
uid_32 cppgram::CoreBot::sendMessage(const T& id, const std::string& text,const Json::Value& reply_markup,
                                     const ParseMode& parse_mode,const bool& disable_web_page_preview,
                                     const bool& disable_notification,const uid_32& reply_to_message_id) const
{
    string parseMode="",fid;
    
    if(typeid(id) == typeid(fid)) 
        fid=id;
    else
        fid=to_string(id);
    
    if(parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if(parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";
    
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/sendMessage"},
                                            cpr::Parameters{{"chat_id",to_string(chatId)}, {"text", text},
                                  {"parse_mode", parseMode},
                                  {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                  {"disable_notification", to_string(disable_notification)},
                                  {"reply_to_message_id", to_string(reply_to_message_id)},
                                  {"reply_markup", writer->write(reply_markup)}});
    Json::Value valroot;

    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"]["message_id"].asUInt();
}
