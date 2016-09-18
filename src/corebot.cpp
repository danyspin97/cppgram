#include <cpr/cpr.h>
#include <json/json.h>
#include "cppgram/cppgram.h"

//DEBUG
#include <iostream>


using namespace cppgram;
using namespace std;

CoreBot::CoreBot(const string &api_token, const string& botusern,const bool &background,
                 const string &filename,const uid_32 &timeout, const uid_32 &message_limit)
        : Logger(filename), bot_token(api_token), bot_usern(botusern), updateId(0),
         timeout(timeout),
          msg_limit(message_limit)
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
  
}

void CoreBot::run()
{
    getUpdates();
}

bool CoreBot::checkMethodError(const cpr::Response& response, Json::Value& val) const
{
    // If there was an error in the connection print it
    if (response.error.code != cpr::ErrorCode::OK) {
        log_error("HTTP Error:" + response.error.message);
        return false;
    }

    if(!Singleton::getInstance()->getReader()->parse(response.text, val)) {
        log_error("JSON Parser: Error while parsing JSON document!");
        throw new JsonParseError;
    }

    // Print method error
    if(response.status_code != 200) {
        log_error("Telegram Error: " + val["error_code"].asString() + ", Description: " + val["description"].asString());
        return false;
    }

    return true;
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
         if (checkMethodError(response, valroot) && !valroot["result"].empty()) {
             for(Json::Value &val: valroot["result"]) {
                 async(processUpdate, val, 0);
                 updateId = val["update_id"].asUInt();
                 log_event("Last update ID: "+to_string(updateId));
             }
         }
     }
}

short CoreBot::processUpdate(Json::Value &val, const short thread_number)
{
    if (!val["message"].isNull()) {
        chatId[thread_number] = val["message"]["chat"]["id"].asInt64();
        processMessage(message(val["message"], bot_usern), thread_number);
        chatId[thread_number] = 0;
    } else if (!val["edited_message"].isNull()) {
        chatId[thread_number] = val["edited_message"]["chat"]["id"].asInt64();
        processEditedMessage(message(val["edited_message"], bot_usern), thread_number);
        chatId[thread_number] = 0;
    } else if (!val["inline_query"].isNull()) {
        inlineQueryId[thread_number] = val["inline_query"]["id"].asString();
        processInlineQuery(inlineQuery(val["inline_query"]), thread_number);
        inlineQueryId[thread_number] = "";
    } else if (!val["choosen_inline_result"].isNull()) {
        processChosenInlineResult(choosenInlineResult(val["choosen_inline_result"]), thread_number);
    } else if (!val["callback_query"].isNull()) {
        callbackQueryId[thread_number] = val["callback_query"]["id"].asString();
        chatId[thread_number] = val["callback_query"]["message"]["chat"]["id"].asInt64();
        messageId[thread_number] = val["callback_query"]["message"]["message_id"].asUInt();
        processCallbackQuery(callbackQuery(val["callback_query"], bot_usern), thread_number);
        callbackQueryId[thread_number] = "";
        chatId[thread_number] = 0;
        messageId[thread_number] = 0;
    }
}

//virtual functions
void CoreBot::processMessage(const struct message& message, const short thread_number) {}
void CoreBot::processEditedMessage(const struct message& editedMessage, const short thread_number) {}
void CoreBot::processInlineQuery(const struct inlineQuery& inlineQuery, const short thread_number) {}
void CoreBot::processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult, const short thread_number) {}
void CoreBot::processCallbackQuery(const struct callbackQuery& callbackQuery, const short thread_number ){}
//
