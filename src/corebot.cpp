#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/cppgram.h"

using namespace cppgram;
CoreBot::CoreBot(const std::string &api_token, bool background,
                const std::string &filename,int timeout, int message_limit)
        : Logger(filename), bot_token(api_token), lastUpdateId(0),lastChatId(0),
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

void cppgram::CoreBot::sendMessage(const std::string& text, ParseMode pmode, const std::string& customChatId, bool disable_web_page_preview, bool disable_notification, uid_32 reply_to_message_id, void* reply_markup)
{
    std::string parseMode, choosenChatId=std::to_string(lastChatId);
    if(pmode == ParseMode::HTML)
        parseMode="HTML";
    else if(pmode == ParseMode::Markdown)
        parseMode="Markdown";
    
    if(customChatId != SENDMSG_DEFAULT_CHATID)
        choosenChatId=customChatId;

    std::string fullURL = std::string(TELEGRAMAPI)+bot_token
            +"/sendMessage?text="
            +text+"&chat_id="
            +choosenChatId
            +"&parse_mode="
            +parseMode
            +"&disable_notification="
            +std::to_string(disable_notification)
            +"&disable_web_page_preview="
            +std::to_string(disable_web_page_preview);

    if(reply_to_message_id != 0 && reply_to_message_id > 0)
        fullURL+"&reply_to_message_id="+std::to_string(reply_to_message_id);

    const cpr::Response response = cpr::Get(cpr::Url{fullURL});
    if(response.status_code != 200) {
        log_warn("(sendMessage) HTTP Response status code is not 200: "+std::to_string(response.status_code));
    } else {
        std::string json_doc = response.text;
        Json::Value valroot;
        Json::Reader reader;

        if(!reader.parse(json_doc.c_str(),valroot)) {
            log_error("(sendMessage) Error while parsing JSON document!");
            throw new JsonParseError;
        }

        if(!valroot["ok"].isBool() || valroot["ok"].isNull())
            log_warn("Maybe a malformed JSON document...");

        if (!valroot["ok"].asBool()) {
            log_warn("(sendMessage) \"ok\" is not true!");
            throw new NotOkTelegramAPI;
        }
        
        log_event("Sent message to chatId/@usernchan: "+choosenChatId+", text: "+text+", parse mode: "+parseMode);
    }
}

void CoreBot::getUpdates()
{
     while(1) {
         const cpr::Response response = cpr::Get(cpr::Url{std::string(TELEGRAMAPI)
                                                  +bot_token
                                                  +"/getUpdates?timeout="
                                                  +std::to_string(timeout)
                                                  +"&limit="
                                                  +std::to_string(msg_limit)
                                                  +"&offset="
                                                  +std::to_string(lastUpdateId+1)
        });

        if(response.status_code != 200) {
            log_warn("(getUpdates) Response status code is not 200: "+response.status_code);
        } else {
            std::string json_doc = response.text;
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


                log_event("Last update ID: "+std::to_string(lastUpdateId)+", last chat ID: "+std::to_string(lastChatId));
            }
        }
    }
}

void CoreBot::processUpdate(Json::Value &val)
{
    if (!val["message"].isNull()) {
        struct message m = message(val["message"]);
        lastChatId = val["message"]["chat"]["id"].asInt64();
        log_event("Got a message: "+m.text+", from: "+m.from->username+", message ID: "+std::to_string(m.message_id));
        processMessage(m);
    } else if (!val["edited_message"].isNull()) {
        struct message editedMessage = message(val["edited_message"]);
        lastChatId = val["edited_message"]["chat"]["id"].asInt64();
        log_event("Got an edited message: "+editedMessage.text+", from: "+editedMessage.from->username+", message ID: "+std::to_string(editedMessage.message_id));
        processEditedMessage(editedMessage);
    } else if (!val["inline_query"].isNull()) {
        struct inlineQuery iquery = inlineQuery(val["inline_query"]);
        log_event("Got an inline query: "+iquery.query+", from: "+iquery.from->username+", query ID: "+iquery.id);
        processInlineQuery(iquery);
    } else if (!val["choosen_inline_result"].isNull()) {
        struct choosenInlineResult chooseninlres = choosenInlineResult(val["choosen_inline_result"]);
        log_event("Got a choosen inline result: "+chooseninlres.result_id+", from: "+chooseninlres.from->username+", query: "+chooseninlres.query+ ", query msg ID: "+std::to_string(chooseninlres.inline_message_id));
        processChosenInlineResult(chooseninlres);
    } else if (!val["callback_query"].isNull()) {
        struct callbackQuery cbquery = callbackQuery(val["callback_query"]);
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
