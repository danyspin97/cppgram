#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/defines.h"
#include "cppgram/telegrambot.h"
#include "cppgram/exceptions.h"
#include "cppgram/singleton.h"
#include "cppgram/utils.h"
#include "cppgram/structures.h"

using namespace cppgram;
using namespace std;

using util::Log;
using util::log;

TelegramBot::TelegramBot(const string &api_token, const string& botusern,const bool &background,
                 const string &filename,const uid_32 &timeout, const uid_32 &message_limit)
        : bot_token(api_token), bot_usern(botusern), updateId(0),
         timeout(timeout),
          msg_limit(message_limit)
{
    if(background) {
        int bg=osutil::backgroundProcess();
        if (bg == OSUTIL_NEWPROC_NOTSUPPORTED) {
            log(Log::Error,"Your operating system is not supported (not yet) for background process");
            throw new BgProcessOSNotSupported;
        } else if(bg == OSUTIL_NEWPROC_FAILED) {
            log(Log::Error,"Error while creating background process");
            throw new BgProcessFailed;
        } else if(bg == OSUTIL_NEWPROC_SUCCESS)
            log(Log::Event,"New background process created!!");
    }

    reader = Singleton::getInstance()->getReader();
    Singleton::getInstance()->setLogFilename(filename);
}

void TelegramBot::run()
{
    getUpdates();
}

bool TelegramBot::checkMethodError(const cpr::Response& response, Json::Value& val) const
{
    // If there was an error in the connection print it
    if (response.error.code != cpr::ErrorCode::OK) {
        log(Log::Error,"HTTP Error:" + response.error.message);
        return false;
    }

    if(!reader->parse(response.text, val)) {
        log(Log::Error,"JSON Parser: Error while parsing JSON document!");
        throw new JsonParseError;
    }

    // Print method error
    if(response.status_code != 200) {
        log(Log::Error,"Telegram Error: " + val["error_code"].asString() + ", Description: " + val["description"].asString());
        return false;
    }

    return true;
}

// Ask telegram to send all updates that need to be parsed
void TelegramBot::getUpdates()
{
     while(1) {
         const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI+bot_token+"/getUpdates"}, 
                                                 cpr::Parameters{{"timeout", to_string(timeout)},
                                                 {"limit", to_string(msg_limit)},
                                                 {"offset", to_string(updateId + 1)}});
         
         Json::Value valroot;
         if (checkMethodError(response, valroot) && !valroot["result"].empty()) {
             for(Json::Value &val: valroot["result"]) {
                 processUpdate(val);
                 updateId = val["update_id"].asUInt();
                 log(Log::Event,"Last update ID: "+to_string(updateId));
             }
         }
     }
}

void TelegramBot::processUpdate(Json::Value &val)
{
    if (!val["message"].isNull()) {
        processMessage(message(val["message"], bot_usern));
    } else if (!val["edited_message"].isNull()) {
        processEditedMessage(message(val["edited_message"], bot_usern));
    } else if (!val["inline_query"].isNull()) {
        processInlineQuery(inlineQuery(val["inline_query"]));
    } else if (!val["choosen_inline_result"].isNull()) {
        processChosenInlineResult(choosenInlineResult(val["choosen_inline_result"]));
    } else if (!val["callback_query"].isNull()) {
        processCallbackQuery(callbackQuery(val["callback_query"], bot_usern));
    }
}

//virtual functions
void TelegramBot::processMessage(const struct message& message) {}
void TelegramBot::processEditedMessage(const struct message& editedMessage) {}
void TelegramBot::processInlineQuery(const struct inlineQuery& inlineQuery) {}
void TelegramBot::processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult) {}
void TelegramBot::processCallbackQuery(const struct callbackQuery& callbackQuery){}
//

bool TelegramBot::editMessageText(const string& inline_message_id,
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
            response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageText"},
                                cpr::Parameters{{"inline_message_id", inline_message_id},
                                                {"text", text},
                                                {"parse_mode", parseMode},
                                                {"disable_web_page_preview", disable_web_page_preview},
                                                {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return 1;

    return valroot["result"].asBool();
}

bool TelegramBot::answerInlineQuery(const string &inline_query_id,
                                    const string &results,
                                    const int &cache_time,
                                    const bool &is_personal,
                                    const string &next_offset,
                                    const string &switch_pm_text,
                                    const string &switch_pm_paramter)
{
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/answerInlineQuery"},
                                            cpr::Parameters{{"inline_query_id", inline_query_id},
                                                            {"results", results},
                                                            {"cache_time", to_string(cache_time)},
                                                            {"is_personal", is_personal},
                                                            {"next_offset", next_offset},
                                                            {"switch_pm_text", switch_pm_paramter},
                                                            {"switch_pm_parameter", switch_pm_paramter}});


    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return false;

    return valroot["result"].asBool();
}
