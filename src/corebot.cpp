#include <iostream>
#include "cpr/cpr.h"
#include "json/json.h"
#include "cppgram/cppgram.h"

using namespace cppgram;

CoreBot::CoreBot(const char* api_token, bool background,
                const char* filename,int timeout, int message_limit)
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

void CoreBot::sendMessage(const char* text,
                                   ParseMode pmode,
                                   bool disable_web_page_preview,
                                   bool disable_notification,
                                   uid_32 reply_to_message_id,
                                   void* reply_markup) const
{
    log_event("sending");
    char fmt[256];
    std::string parseMode;
    if(pmode == ParseMode::HTML)
        parseMode="HTML";
    else if(pmode == ParseMode::Markdown)
        parseMode="Markdown";

    std::string fullURL = std::string(TELEGRAMAPI).append(bot_token)
            .append("/sendMessage?text=")
            .append(text).append("&chat_id=")
            .append(std::to_string(lastChatId))
            .append("&parse_mode=")
            .append(parseMode)
            .append("&disable_notification=")
            .append(std::to_string(disable_notification))
            .append("&disable_web_page_preview=")
            .append(std::to_string(disable_web_page_preview));

    if(reply_to_message_id != 0 && reply_to_message_id > 0)
        fullURL.append("&reply_to_message_id=").append(std::to_string(reply_to_message_id));

    cpr::Response response = cpr::Get(cpr::Url{fullURL});
    if(response.status_code != 200) {
        sprintf(fmt, "(sendMessage) HTTP Response status code is not 200: %d", response.status_code);
        log_warn(fmt);
        throw new NoHTTPOKResponse;
    } else {
        std::string json_doc = response.text;
        Json::Value valroot;
        Json::Reader reader;

        if(!reader.parse(json_doc.c_str(),valroot)) {
            log_error("(sendMessage) Error while parsing JSON document!");
            throw new JsonParseError;
        }

        if(!valroot["ok"].isBool() || valroot["ok"].isNull())
            throwMalformedJson();

        if (!valroot["ok"].asBool()) {
            log_warn("(sendMessage) \"ok\" is not true!");
            throw new NotOkTelegramAPI;
        }
    }
}

void CoreBot::getUpdates()
{
     while(1) {
        char fmt[256];
         //TODO
         cpr::Response response = cpr::Get(cpr::Url{std::string(TELEGRAMAPI)
                                                  .append(bot_token)
                                                  .append("/getUpdates?timeout=")
                                                  .append(std::to_string(timeout))
                                                  .append("&limit=")
                                                  .append(std::to_string(msg_limit))
                                                  .append("&offset=")
                                                  .append(std::to_string(lastUpdateId+1))
        });

        if(response.status_code != 200) {
            sprintf(fmt, "HTTP Response status code is not 200: %d", response.status_code);
            log_warn(fmt);
            throw new NoHTTPOKResponse;
        } else {
            std::string json_doc = response.text;
            Json::Value valroot;
            Json::Reader doc_reader;
            if (!doc_reader.parse(json_doc, valroot)) {
                log_error("Error while parsing JSON document!");
                throw new JsonParseError;
            }


            if(!valroot["ok"].isBool() || valroot["ok"].isNull())
                throwMalformedJson();

            if(valroot["result"].isNull() || !valroot["result"].isArray())
                throwMalformedJson();

            if (!valroot["ok"].asBool()) {
                log_warn("\"ok\" is not true!");
                throw new NotOkTelegramAPI;
            }

            if (valroot["ok"].asBool() && valroot["result"].empty()) continue;

            for(Json::Value val: valroot["result"]) {
                //parseAssignExecuteUpdate(val);

                processUpdate(val);
                lastUpdateId = val["update_id"].asLargestUInt();
                log_event(std::string("Last Update ID: ")
                                  .append(std::to_string(lastUpdateId))
                                  .c_str());
            }
        }
    }
}

void CoreBot::processUpdate(Json::Value &val)
{

    log_event("here");
    message message1(val["message"]);
    log_event(message1.text.c_str());
    processMessage(message1);
    if (!val["message"].isNull()) {
        std::cout << "message arrived";
        processMessage(message(val["message"]));
    }
    else if (!val["edited_message"].isNull())
        processEditedMessage(message(val["edited_message"]));
    else if (!val["inline_query"].isNull())
        processInlineQuery(inlineQuery(val["inline_query"]));
    else if (!val["choosen_inline_result"].isNull())
        processChosenInlineResult(choosenInlineResult(val["choosen_inline_result"]));
    else if (!val["callback_query"].isNull())
        processCallbackQuery(callbackQuery(val["callback_query"]));
}

//virtual functions
void CoreBot::processMessage(const struct message& message) {}
void CoreBot::processEditedMessage(const struct message& editedMessage) {}
void CoreBot::processInlineQuery(const struct inlineQuery& inlineQuery) {}
void CoreBot::processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult) {}
void CoreBot::processCallbackQuery(const struct callbackQuery& callbackQuery) {}
//

void CoreBot::throwMalformedJson() const
{
    log_error("Malformed JSON document!!");
    throw new MalformedJsonDocument;
}
