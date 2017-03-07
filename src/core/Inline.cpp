#include "CoreBot.hpp"

using std::string;
using std::to_string;

using cppgram::CoreBot;
using cppgram::message;

bool
CoreBot::answerInlineQuery(const string&      inline_query_id,
                           const Json::Value& results,
                           const int          cache_time,
                           const bool         is_personal,
                           const string&      next_offset,
                           const string&      switch_pm_text,
                           const string&      switch_pm_paramter)
{
    Json::FastWriter writer;

    auto response = executeRequest(
            "answerInlineQuery",
            cpr::Parameters{{"inline_query_id", inline_query_id},
                            {"results", writer.write(results)},
                            {"cache_time", to_string(cache_time)},
                            {"is_personal", is_personal},
                            {"next_offset", next_offset},
                            {"switch_pm_text", switch_pm_paramter},
                            {"switch_pm_parameter", switch_pm_paramter}});

    Json::Value valroot;
    if (!checkMethodError(response, valroot)) {
        return false;
    }

    return valroot["result"].asBool();
}
