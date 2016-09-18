#ifndef CPPGRAM_INLINEQUERYRESULT_H
#define CPPGRAM_INLINEQUERYRESULT_H

#include <string>

namespace cppgram
{

enum ParseMode : short;

class InlineQueryResult
{
    public:
    InlineQueryResult();
    short newArticle(const std::string &title,
                     const std::string &message_text,
                     const std::string &description,
                     const Json::Value &reply_markup = Json::Value(),
                     ParseMode parse_mode = static_cast<ParseMode>(0),
                     bool disable_web_page_preview = true);

    const Json::Value &getResults();

    private:
    Json::Value results;
    short articleId;
};

}
#endif //CPPGRAM_INLINEQUERYRESULT_H
