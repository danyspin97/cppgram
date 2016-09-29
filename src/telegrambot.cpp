#include <cpr/cpr.h>
#include <json/json.h>

#include <future>
#include <chrono>

#include "cppgram/defines.h"
#include "cppgram/telegrambot.h"
#include "cppgram/exceptions.h"
#include "cppgram/singleton.h"
#include "cppgram/utils.h"
#include "cppgram/structures.h"

using namespace cppgram;
using namespace std;
using namespace util;

TelegramBot::TelegramBot(const string &api_token, const bool &background,
                         const string &filename, const uid_32 &timeout, const uid_32 &limit)
        : bot_token(api_token), updateId(0),
          timeout(timeout), update_limit(limit)
{

    if (background) {
        int bg = osutil::backgroundProcess();
        if (bg == OSUTIL_NEWPROC_NOTSUPPORTED) {
            log(Log::Error, "Your operating system is not supported (not yet) for background process");
            throw new BgProcessOSNotSupported;
        } else if (bg == OSUTIL_NEWPROC_FAILED) {
            log(Log::Error, "Error while creating background process");
            throw new BgProcessFailed;
        } else if (bg == OSUTIL_NEWPROC_SUCCESS)
            log(Log::Event, "New background process created!!");
    }
    Singleton::getInstance()->setLogFilename(filename);
}

void TelegramBot::run()
{
    processUpdates();
}

void TelegramBot::parseUpdate(Json::Value valroot)
{
    if (!valroot["result"][0]["message"].isNull()) {
        processMessage(message(valroot["result"][0]["message"]));
    } else if (!valroot["result"][0]["edited_message"].isNull()) {
        processEditedMessage(message(valroot["result"][0]["edited_message"]));
    } else if (!valroot["result"][0]["inline_query"].isNull()) {
        processInlineQuery(inlineQuery(valroot["result"][0]["inline_query"]));
    } else if (!valroot["result"][0]["choosen_inline_result"].isNull()) {
        processChosenInlineResult(choosenInlineResult(valroot["result"][0]["choosen_inline_result"]));
    } else if (!valroot["result"][0]["callback_query"].isNull()) {
        processCallbackQuery(callbackQuery(valroot["result"][0]["callback_query"]));
    }
}

// Ask telegram to send all updates that need to be parsed
void TelegramBot::processUpdates()
{
    const std::string &botok = bot_token;
    thread keepAliveTimer([&botok] {
        while(1) {
            request(cpr::Url {TELEGRAMAPI+botok});
            this_thread::sleep_for(chrono::seconds(68));
        }
    });
    keepAliveTimer.detach();

    vector<future<void>> vecfuts;
    while (1) {
        const cpr::Response response = request(cpr::Url{TELEGRAMAPI + bot_token + "/getUpdates"},
                                               cpr::Parameters{{"timeout", to_string(timeout)},
                                                  {"limit", to_string(update_limit)},
                                                  {"offset", to_string(updateId+1)}});
        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty()) {
            vecfuts.push_back(async(launch::async,&TelegramBot::parseUpdate,this,valroot));
            updateId = valroot["result"][0]["update_id"].asUInt();
        }

        async(launch::async, [&vecfuts] {
            for(uid_32 i=0;i<=vecfuts.size()-1;i++) {
                if(vecfuts.at(i).wait_for(chrono::seconds(0)) == future_status::ready) {
                    vecfuts.erase(vecfuts.begin() + i);
                }
            }
        });

        this_thread::sleep_for(chrono::milliseconds(1));
    }
}

bool TelegramBot::getUpdates(Json::Value &val, const uid_32 &offset, const uid_32 &limit, const uid_32 &timeout)
{
    const cpr::Response response = request(cpr::Url{TELEGRAMAPI + bot_token + "/getUpdates"},
                                           cpr::Parameters{{"timeout", to_string(timeout)},
                                                           {"limit", to_string(limit)},
                                                           {"offset", to_string(offset + 1)}});
    if (!checkMethodError(response, val))
        return false;

    return true;
}

bool TelegramBot::editMessageText(const string &inline_message_id,
                                  const string &text,
                                  const string &reply_markup,
                                  const ParseMode &parse_mode,
                                  const bool &disable_web_page_preview) const
{
    string parseMode = "";

    if (parse_mode == ParseMode::HTML)
        parseMode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        parseMode = "Markdown";

    const cpr::Response response = request(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageText"},
                                           cpr::Parameters{{"inline_message_id", inline_message_id},
                                                           {"text", text},
                                                           {"parse_mode", parseMode},
                                                           {"disable_web_page_preview", disable_web_page_preview},
                                                           {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return false;

    return valroot["result"].asBool();
}

bool TelegramBot::editMessageReplyMarkup(const string &inline_message_id,
                                         const string &reply_markup) const
{
    const cpr::Response response = request(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageReplyMarkup"},
                                           cpr::Parameters{{"inline_message_id", inline_message_id},
                                                           {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return false;

    return valroot["result"].asBool();
}

bool TelegramBot::editMessageCaption(const string &inline_message_id,
                                     const string &caption,
                                     const string &reply_markup) const
{
    const cpr::Response response = request(cpr::Url{TELEGRAMAPI + bot_token + "/editMessageCaption"},
                                           cpr::Parameters{{"inline_message_id", inline_message_id},
                                                           {"caption", caption},
                                                           {"reply_markup", reply_markup}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
        return false;

    return valroot["result"].asBool();
}

bool TelegramBot::answerInlineQuery(const string &inline_query_id,
                                    const string &results,
                                    const int &cache_time,
                                    const bool &is_personal,
                                    const string &next_offset,
                                    const string &switch_pm_text,
                                    const string &switch_pm_paramter) const
{
    const cpr::Response response = request(cpr::Url{TELEGRAMAPI + bot_token + "/answerInlineQuery"},
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

//virtual functions
void TelegramBot::processMessage(const struct message &message)
{}
void TelegramBot::processEditedMessage(const struct message &editedMessage)
{}
void TelegramBot::processInlineQuery(const struct inlineQuery &inlineQuery)
{}
void TelegramBot::processChosenInlineResult(const struct choosenInlineResult &choosenInlineResult)
{}
void TelegramBot::processCallbackQuery(const struct callbackQuery &callbackQuery)
{}
//
