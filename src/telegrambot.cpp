#include <cpr/cpr.h>
#include <json/json.h>

#include <future>
#include <thread>
#include <chrono>
#include <mutex>

#include "cppgram/defines.h"
#include "cppgram/telegrambot.h"
#include "cppgram/exceptions.h"
#include "cppgram/singleton.h"
#include "cppgram/utils.h"


// DEBUG
#include <iostream>

using namespace cppgram;
using namespace std;
using namespace util;

std::mutex mtut;

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
    unsigned num_cps = thread::hardware_concurrency();
    if (num_cps > 1) {
        sessions.push_back(new cpr::Session);
        vector<thread> threads(num_cps - 1);
        for (unsigned i = 1; i < num_cps; i++) {
            sessions.push_back(new cpr::Session);
            threads[i - 1] = thread(&TelegramBot::processUpdates, this);
            cpu_set_t cpuset_updates;
            CPU_ZERO(&cpuset_updates);
            CPU_SET(i, &cpuset_updates);
            int tf = pthread_setaffinity_np(threads[i - 1].native_handle(),
                                            sizeof(cpu_set_t), &cpuset_updates);
            if (tf != 0) {
                throw new ThreadException;
            }
        }
        queueUpdates();
        for (auto &t : threads) {
            t.join();
        }
    }
}
// Ask telegram to send all updates that need to be parsed
void TelegramBot::queueUpdates()
{
    //runOnce, needed in order to get the initial update_id offset
    //this will not be executed more than 1 time, after the first update
    do {
        const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + bot_token + "/getUpdates"},
                                                cpr::Parameters{{"timeout", to_string(timeout)},
                                                                {"limit", to_string(update_limit)},
                                                                {"offset", to_string(updateId)}});
        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty()) {
            //sets the initial offset
            updateId = valroot["result"][0]["update_id"].asUInt();
        }
    } while (updateId == 0);
    while (1) {
        sessions[0]->SetUrl(cpr::Url{TELEGRAMAPI + bot_token + "/getUpdates"});
        sessions[0]->SetParameters(cpr::Parameters{{"timeout", to_string(timeout)},
                                                   {"limit", to_string(update_limit)},
                                                   {"offset", to_string(updateId)}});
        const cpr::Response response = sessions[0]->Get();
        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty()) {
            for (Json::Value &val: valroot["result"]) {
                mtut.lock();
                updates_queue.push_back(update(val));
                mtut.unlock();
            }
            updateId += valroot["result"].size();
        }
    }
}

void TelegramBot::processUpdates()
{
    while (1) {
        mtut.lock();
        if (updates_queue.size() > 0) {
            update new_update = updates_queue.front();
            updates_queue.pop_front();
            mtut.unlock();
            switch (new_update.type) {
                case UpdateType::Message:processMessage(*new_update.message);
                    break;
                case UpdateType::CallbackQuery:processCallbackQuery(*new_update.callbackQuery);
                    break;
                case UpdateType::EditedMessage:processEditedMessage(*new_update.message);
                    break;
                case UpdateType::InlineQuery:processInlineQuery(*new_update.inlineQuery);
                    break;
                case UpdateType::ChoosenInlineResult: processChosenInlineResult(*new_update.choosenInlineResult);
                    break;
            }
        } else {
            mtut.unlock();
        }
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
