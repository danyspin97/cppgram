#include <json/json.h>
#include "cppgram/cppgram.h"

bool InlineQueryBot::answerInlineQuery(const std::string &inline_query_id,
                                       const std::string &results,
                                       int cache_time,
                                       bool is_personal,
                                       const std::string &next_offset,
                                       const std::string &switch_pm_text,
                                       const std::string &switch_pm_paramter)
{
    const cpr::Response response = cpr::Get(cpr::Url{TELEGRAMAPI + Singleton::getInstance()->getToken() + "/sendMessage"},
                                            cpr::Parameters{{"inline_query_id", inline_query_id},
                                                            {"results", results},
                                                            {"cache_time", to_string(cache_time)},
                                                            {"is_personal", is_personal},
                                                            {"next_offset", next_offset},
                                                            {"switch_pm_text", switch_pm_paramter},
                                                            {"switch_pm_parameter", switch_pm_paramter}});

    Json::Value valroot;
    //if (!checkMethodError(response, valroot))
    //    return false;

    return valroot["result"].asBool();
}
