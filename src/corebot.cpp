#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/cppgram.h"
#include "cppgram/osutil.h"

using namespace cppgram;
using std::string;
using std::to_string;

CoreBot::CoreBot(const string &api_token, const string& botusern,bool background,
                const string &filename,int timeout, int message_limit)
        : Logger(filename), bot_token(api_token), bot_usern(botusern),lastUpdateId(0),lastChatId(0),
          timeout(timeout), msg_limit(message_limit)
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

void CoreBot::run()
{
    getUpdates();
}

void cppgram::CoreBot::sendMessage(const string& text, ParseMode parse_mode, bool disable_web_page_preview, bool disable_notification, uid_32 reply_to_message_id, void* reply_markup)
{
    string parseMode="HTML", id=to_string(lastChatId);
    if(parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if(parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";
    
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/sendMessage"},
                  cpr::Parameters{{"chat_id", id}, {"text", text},
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

        log_event("Sent message to chatId/@usernchan: "+id+", text: "+text+", parse mode: "+parseMode);
    }
}
void CoreBot::getUpdates()
{
     while(1) {
         const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/getUpdates"}, 
                                                 cpr::Parameters{{"timeout",to_string(timeout)},
                                                 {"limit",to_string(msg_limit)}, 
                                                 {"offset",to_string(lastUpdateId+1)}});

        if(response.status_code != 200) {
            log_warn("(getUpdates) Response status code is not 200: "+to_string(response.status_code));
        } else {
            string json_doc = response.text;
            Json::Value valroot;
            Json::Reader doc_reader;
            if (!doc_reader.parse(json_doc, valroot)) {
                log_error("Error while parsing JSON document!");
                throw new JsonParseError;
            }

            if(!valroot["ok"].isBool() || valroot["ok"].isNull())
                log_warn("Maybe a malformed JSON document...");

            if(valroot["result"].isNull() || !valroot["result"].isArray())
                log_warn("Maybe a malformed JSON document...");

            if (!valroot["ok"].asBool()) {
                log_warn("\"ok\" is not true!");
                throw new NotOkTelegramAPI;
            }

            if (valroot["ok"].asBool() && valroot["result"].empty()) continue;

            for(Json::Value val: valroot["result"]) {
                processUpdate(val);
                lastUpdateId = val["update_id"].asLargestUInt();


                log_event("Last update ID: "+to_string(lastUpdateId)+", last chat ID: "+to_string(lastChatId));
            }
        }
    }
}

void CoreBot::processUpdate(Json::Value &val)
{
    if (!val["message"].isNull()) {
        struct message m = message(val["message"], bot_usern);
        lastChatId = val["message"]["chat"]["id"].asInt64();
        log_event("Got a message: "+m.text+", from: "+m.from->username+", message ID: "+to_string(m.message_id));
        processMessage(m);
    } else if (!val["edited_message"].isNull()) {
        struct message editedMessage = message(val["edited_message"], bot_usern);
        lastChatId = val["edited_message"]["chat"]["id"].asInt64();
        log_event("Got an edited message: "+editedMessage.text+", from: "+editedMessage.from->username+", message ID: "+to_string(editedMessage.message_id));
        processEditedMessage(editedMessage);
    } else if (!val["inline_query"].isNull()) {
        struct inlineQuery iquery = inlineQuery(val["inline_query"]);
        log_event("Got an inline query: "+iquery.query+", from: "+iquery.from->username+", query ID: "+iquery.id);
        processInlineQuery(iquery);
    } else if (!val["choosen_inline_result"].isNull()) {
        struct choosenInlineResult chooseninlres = choosenInlineResult(val["choosen_inline_result"]);
        log_event("Got a choosen inline result: "+chooseninlres.result_id+", from: "+chooseninlres.from->username+", query: "+chooseninlres.query+ ", query msg ID: "+to_string(chooseninlres.inline_message_id));
        processChosenInlineResult(chooseninlres);
    } else if (!val["callback_query"].isNull()) {
        struct callbackQuery cbquery = callbackQuery(val["callback_query"], bot_usern);
        log_event("Got a callback query: "+cbquery.data+", from: "+cbquery.from->username+", cbquery ID: "+cbquery.id);
        processCallbackQuery(cbquery);
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
