#include <cpr/cpr.h>
#include <json/json.h>

#include <future>
#include <thread>
#include <chrono>
#include <mutex>
#include <algorithm>

#include "cppgram/telegrambot.h"
#include "cppgram/types/update.h"
#include "cppgram/defines.h"
#include "cppgram/exceptions.h"
#include "cppgram/utils.h"
#include "cppgram/commands/messagecommands.h"

using std::thread;
using std::vector;

using namespace cppgram;

std::mutex mutex;

TelegramBot::TelegramBot(const string &apiToken, const bool &background,
                         const int_fast32_t &timeout, const int_fast32_t &limit)
        : botToken(apiToken), timeout(timeout), updateLimit(limit),
          messageCommands_set(false)
{
    if (background)
    {
        int bg = osutil::backgroundProcess();
        if (bg == OSUTIL_NEWPROC_NOTSUPPORTED)
        {
            log(Log::Error, "Your operating system is not supported (not yet) for background process");
            throw BgProcessOSNotSupported();
        }
        else if (bg == OSUTIL_NEWPROC_FAILED)
        {
            log(Log::Error, "Error while creating background process");
            throw BgProcessFailed();
        }
        else if (bg == OSUTIL_NEWPROC_SUCCESS)
        {
            log(Log::Event, "New background process created!!");
        }
    }
}

bool TelegramBot::getUpdates(Json::Value &updates, const int_fast32_t &offset, const int_fast32_t &limit, const int_fast32_t &timeout)
{
    int cpu_id = sched_getcpu();

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/getUpdates"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"timeout", to_string(timeout)},
                                                    {"limit", to_string(limit)},
                                                    {"offset", to_string(offset + 1)}});

    const cpr::Response response = sessions[cpu_id]->Get();
    if (!checkMethodError(response, updates))
    {
        return false;
    }

    if (updates["result"].empty())
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool TelegramBot::editMessageText(const string &inline_message_id,
                                  const string &text,
                                  const string &reply_markup,
                                  const ParseMode &parse_mode,
                                  const bool &disable_web_page_preview) const
{
    string parseMode = "";

    if (parse_mode == ParseMode::HTML)
    {
        parseMode = "HTML";
    }
    else if (parse_mode == ParseMode::Markdown)
    {
        parseMode = "Markdown";
    }

    int cpu_id = sched_getcpu();

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/editMessageText"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"inline_message_id", inline_message_id},
                                                    {"text", text},
                                                    {"parse_mode", parseMode},
                                                    {"disable_web_page_preview", disable_web_page_preview},
                                                    {"reply_markup", reply_markup}});

    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
    {
        return false;
    }

    return valroot["result"].asBool();
}

bool TelegramBot::editMessageCaption(const string &inline_message_id,
                                     const string &caption,
                                     const string &reply_markup) const
{
    int cpu_id = sched_getcpu();

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/editMessageCaption"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"inline_message_id", inline_message_id},
                                                    {"caption", caption},
                                                    {"reply_markup", reply_markup}});

    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
    {
        return false;
    }

    return valroot["result"].asBool();
}

bool TelegramBot::editMessageReplyMarkup(const string &inline_message_id,
                                         const string &reply_markup) const
{
    int cpu_id = sched_getcpu();

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/editMessageReplyMarkup"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"inline_message_id", inline_message_id},
                                                    {"reply_markup", reply_markup}});
    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
    {
        return false;
    }

    return valroot["result"].asBool();
}

bool TelegramBot::answerInlineQuery(const string &inline_query_id,
                                    const Json::Value &results,
                                    const int &cache_time,
                                    const bool &is_personal,
                                    const string &next_offset,
                                    const string &switch_pm_text,
                                    const string &switch_pm_paramter) const
{
    int cpu_id = sched_getcpu();

    Json::FastWriter writer;

    sessions[cpu_id]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/answerInlineQuery"});
    sessions[cpu_id]->SetParameters(cpr::Parameters{{"inline_query_id", inline_query_id},
                                                    {"results", writer.write(results)},
                                                    {"cache_time", to_string(cache_time)},
                                                    {"is_personal", is_personal},
                                                    {"next_offset", next_offset},
                                                    {"switch_pm_text", switch_pm_paramter},
                                                    {"switch_pm_parameter", switch_pm_paramter}});
    const cpr::Response response = sessions[cpu_id]->Get();

    Json::Value valroot;
    if (!checkMethodError(response, valroot))
    {
        return false;
    }

    return valroot["result"].asBool();
}

void TelegramBot::run()
{
    unsigned num_cps = thread::hardware_concurrency();
    if (num_cps > 1)
    {
        sessions.push_back(new cpr::Session);
        vector<thread> threads(num_cps - 1);
        for (unsigned i = 1; i < num_cps; i++)
        {
            sessions.push_back(new cpr::Session);
            threads[i - 1] = thread(&TelegramBot::processUpdates, this);
            cpu_set_t cpuset_updates;
            CPU_ZERO(&cpuset_updates);
            CPU_SET(i, &cpuset_updates);
            int tf = pthread_setaffinity_np(threads[i - 1].native_handle(),
                                            sizeof(cpu_set_t), &cpuset_updates);
            if (tf != 0)
            {
                throw ThreadException();
            }
        }
        queueUpdates();
        for (auto &t : threads)
        {
            t.join();
        }
    }
    else
    {
        thread single_thread(&TelegramBot::processUpdateSingleThread, this);
        cpu_set_t cpuset_updates;
        CPU_ZERO(&cpuset_updates);
        CPU_SET(0, &cpuset_updates);
        int tf = pthread_setaffinity_np(single_thread.native_handle(),
                                        sizeof(cpu_set_t), &cpuset_updates);
        if (tf != 0)
        {
            throw ThreadException();
        }
    }
}
// Ask telegram to send all updates that need to be parsed
void TelegramBot::queueUpdates()
{
    uint_fast32_t updateId = 0;

    //runOnce, needed in order to get the initial update_id offset
    //this will not be executed more than 1 time, after the first update
    do
    {
        sessions[0]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/getUpdates"});
        sessions[0]->SetParameters(cpr::Parameters{{"timeout", to_string(timeout)},
                                                   {"limit", to_string(updateLimit)},
                                                   {"offset", to_string(updateId)}});
        const cpr::Response response = sessions[0]->Get();

        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty())
        {
            //sets the initial offset
            updateId = valroot["result"][0]["update_id"].asUInt();
        }

    } while (updateId == 0);

    uint_fast32_t time_last_connection = 0, time = 0;

    while (1)
    {
        sessions[0]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/getUpdates"});
        sessions[0]->SetParameters(cpr::Parameters{{"timeout", to_string(timeout)},
                                                   {"limit", to_string(updateLimit)},
                                                   {"offset", to_string(updateId)}});

        const cpr::Response response = sessions[0]->Get();

        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty())
        {

            for (Json::Value &val: valroot["result"])
            {
                update *new_update = new update(val);
                mutex.lock();
                updatesQueue.push_back(new_update);
                mutex.unlock();
            }

            updateId += valroot["result"].size();

        }
        else
        {
            if (time_last_connection != 0 && time_last_connection != 60)
            {
                for (unsigned int i = thread::hardware_concurrency() - 1; i != 1; i--)
                {
                    sessions[i]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/getMe"});
                    sessions[i]->Get();
                }

                time_last_connection = time - getMicroTime();
                time = getMicroTime();
            }
            else
            {
                time_last_connection += time - getMicroTime();
                time = getMicroTime();
            }
        }
    }
}

void TelegramBot::initBot()
{
    messageCommands_set = (messageCommands.size() > 0) ? true : false;
}

void TelegramBot::addMessageCommand(std::string command, MessageScript script)
{
    messageCommands.push_back(new MessageCommand(command, script));
}

void TelegramBot::processUpdates()
{
    while (1)
    {

        mutex.lock();
        if (updatesQueue.size() > 0)
        {

            const update* new_update = updatesQueue.front();
            updatesQueue.pop_front();
            mutex.unlock();
            switch (new_update->type)
            {
                case UpdateType::Message:
                    if (new_update->message->entities.size() > 0 && new_update->message->entities[0]->type == MessageEntityType::bot_command)
                    {
                        messageEntity* commandReceived = new_update->message->entities[0];

                        for (auto currentCommand: messageCommands)
                        {

                            if (currentCommand->length == commandReceived->length && new_update->message->text.compare(commandReceived->offset, commandReceived->length, currentCommand->command) == 0)
                            {
                                currentCommand->script(this, new_update->message);
                                break;
                            }
                        }
                    }
                    else
                    {
                        processMessage(*new_update->message);
                    }
                    break;
                case UpdateType::CallbackQuery:
                    processCallbackQuery(*new_update->callbackQuery);
                    break;
                case UpdateType::EditedMessage:
                    processEditedMessage(*new_update->message);
                    break;
                case UpdateType::InlineQuery:
                    processInlineQuery(*new_update->inlineQuery);
                    break;
                case UpdateType::ChoosenInlineResult:
                    processChosenInlineResult(*new_update->choosenInlineResult);
                    break;
            }

            delete new_update;
        }
        else
        {
            mutex.unlock();
        }

    }
}

void TelegramBot::processUpdateSingleThread()
{
    uint_fast32_t updateId = 0;

    for (unsigned i = 0; i < thread::hardware_concurrency(); i++)
    {
        sessions.push_back(new cpr::Session);
    }

    do
    {
        sessions[0]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/getUpdates"});
        sessions[0]->SetParameters(cpr::Parameters{{"timeout", to_string(timeout)},
                                                   {"limit", to_string(updateLimit)},
                                                   {"offset", to_string(updateId)}});
        const cpr::Response response = sessions[0]->Get();
        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty())
        {
            //sets the initial offset
            updateId = valroot["result"][0]["update_id"].asUInt();
        }
    } while (updateId == 0);

    while (1)
    {
        sessions[0]->SetUrl(cpr::Url{TELEGRAMAPI + botToken + "/getUpdates"});
        sessions[0]->SetParameters(cpr::Parameters{{"timeout", to_string(timeout)},
                                                   {"limit", to_string(updateLimit)},
                                                   {"offset", to_string(updateId)}});
        const cpr::Response response = sessions[0]->Get();

        Json::Value valroot;
        if (checkMethodError(response, valroot) && !valroot["result"].empty())
        {
            for (Json::Value &val: valroot["result"])
            {
                if (!val["message"].isNull())
                {
                    processMessage(message(val["message"]));
                }
                else if (!val["edited_message"].isNull())
                {
                    processEditedMessage(message(val["edited_message"]));
                }
                else if (!val["inline_query"].isNull())
                {
                    processInlineQuery(inlineQuery(val["inline_query"]));
                }
                else if (!val["choosen_inline_result"].isNull())
                {
                    processChosenInlineResult(choosenInlineResult(val["choosen_inline_result"]));
                }
                else if (!val["callback_query"].isNull())
                {
                    processCallbackQuery(callbackQuery(val["callback_query"]));
                }
            }
            updateId += valroot["result"].size();
        }
    }
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
