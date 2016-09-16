#include <cpr/cpr.h>
#include <json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;
using std::string;
using std::to_string;

CoreBot::CoreBot(const string &api_token, const string& botusern,const bool &background,
                 const string &filename,const uid_32 &timeout, const uid_32 &message_limit)
        : Logger(filename), bot_token(api_token), bot_usern(botusern),updateId(0),chatId(0),
          timeout(timeout), msg_limit(message_limit), reader(new Json::Reader)
{
    if(background) {
        int bg=osutil::backgroundProcess();
        if (bg == OSUTIL_NEWPROC_NOTSUPPORTED) {
            log_error("Your operating system is not supported (not yet) for background process");
            throw new BgProcessOSNotSupported;
        } else if(bg == OSUTIL_NEWPROC_FAILED) {
            log_error("Error while creating background process");
            throw new BgProcessFailed;
        } else if(bg == OSUTIL_NEWPROC_SUCCESS)
            log_event("New background process created!!");
    }
}

CoreBot::~CoreBot()
{
    delete reader;
}

void CoreBot::run()
{
    getUpdates();
}

uid_32 cppgram::CoreBot::sendMessage(const string& text,const ParseMode& parse_mode, const bool &disable_web_page_preview, const bool &disable_notification, const uid_32& reply_to_message_id, const void* reply_markup) const
{
    string parseMode;
    cpr::Parameters httpGETparams;
    
    if(parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if(parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";
    
    if(parse_mode == ParseMode::None) { 
        httpGETparams = {{"chat_id", to_string(chatId)}, {"text", text},
                                    {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                    {"disable_notification", to_string(disable_notification)},
                                    {"reply_to_message_id", to_string(reply_to_message_id)}};
    } else {
        httpGETparams = {{"chat_id", to_string(chatId)}, {"text", text},
                                    {"parse_mode",parseMode},
                                    {"disable_web_page_preview", to_string(disable_web_page_preview)},
                                    {"disable_notification", to_string(disable_notification)},
                                    {"reply_to_message_id", to_string(reply_to_message_id)}};
    }
    
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/sendMessage"},httpGETparams);

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

// Ask telegram to send all updates that need to be parsed
void CoreBot::getUpdates()
{
     while(1) {
         const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/getUpdates"}, 
                                                 cpr::Parameters{{"timeout", to_string(timeout)},
                                                 {"limit", to_string(msg_limit)},
                                                 {"offset", to_string(updateId + 1)}});
         Json::Value valroot;

         if (!reader->parse(response.text, valroot)) {
             throw new JsonParseError;
         }

         // Print method error
         if(response.status_code != 200) {
             log_error("Error code: " + valroot["error_code"].asString() + "/n Description: " + valroot["description"].asString());
         }
         
         if(valroot["ok"].asBool() && valroot["result"].empty()) 
             continue;
         
         for(Json::Value& val: valroot["result"]) {
             processUpdate(val);
             updateId = val["update_id"].asUInt();
             log_event("Last update ID: "+to_string(updateId)+", last chat ID: "+to_string(chatId));
         }
     }
}

void CoreBot::processUpdate(Json::Value &val)
{
    if (!val["message"].isNull()) {
        processMessage(message(val["message"], bot_usern));
        chatId=val["message"]["chat"]["id"].asInt64();
    } else if (!val["edited_message"].isNull()) {
        processEditedMessage(message(val["edited_message"], bot_usern));
        chatId=val["message"]["chat"]["id"].asInt64();
    } else if (!val["inline_query"].isNull()) {
        processInlineQuery(inlineQuery(val["inline_query"]));
    } else if (!val["choosen_inline_result"].isNull()) {
        processChosenInlineResult(choosenInlineResult(val["choosen_inline_result"]));
    } else if (!val["callback_query"].isNull()) {
        processCallbackQuery(callbackQuery(val["callback_query"], bot_usern));
    }
}

//virtual functions
void CoreBot::processMessage(const struct message& message) 
{}
void CoreBot::processEditedMessage(const struct message& editedMessage) 
{}
void CoreBot::processInlineQuery(const struct inlineQuery& inlineQuery) 
{}
void CoreBot::processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult)
{}
void CoreBot::processCallbackQuery(const struct callbackQuery& callbackQuery) 
{}
//
