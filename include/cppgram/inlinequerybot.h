#ifndef CPPGRAM_INLINEQUERYBOT_H
#define CPPGRAM_INLINEQUERYBOT_H

#include <string>

namespace cppgram
{

class InlineQueryBot
{
    public:
    bool answerInlineQuery(const std::string& inline_query_id,
                           const std::string& results,
                           int cache_time = 300,
                           bool is_personal = false,
                           const std::string& next_offset = "",
                           const std::string& switch_pm_text = "",
                           const std::string& switch_pm_paramter = "");
};

}

#endif //CPPGRAM_INLINEQUERYBOT_H
