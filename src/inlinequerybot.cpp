#include <cpr/cpr.h>
#include <json/json.h>
#include "cppgram/inlinequerybot.h"
#include "cppgram/defines.h"
#include "cppgram/singleton.h"

using namespace cppgram;
using std::to_string;
using std::string;

bool InlineQueryBot::answerInlineQuery(const string &inline_query_id,
                                       const string &results,
                                       const int &cache_time,
                                       const bool &is_personal,
                                       const string &next_offset,
                                       const string &switch_pm_text,
                                       const string &switch_pm_paramter)
{
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + Singleton::getInstance()->getToken() + "/answerInlineQuery"},
                                            cpr::Parameters{{"inline_query_id", inline_query_id},
                                                            {"results", results},
                                                            {"cache_time", to_string(cache_time)},
                                                            {"is_personal", is_personal},
                                                            {"next_offset", next_offset},
                                                            {"switch_pm_text", switch_pm_paramter},
                                                            {"switch_pm_parameter", switch_pm_paramter}});


    Json::Value valroot;
    if (!Singleton::getInstance()->checkMethodError(response, valroot))
        return false;

    return valroot["result"].asBool();
}
