#ifndef CPPGRAM_INLINEQUERYRESULT_H
#define CPPGRAM_INLINEQUERYRESULT_H

#include <string>

namespace cppgram
{

enum ParseMode : short;

/*! \class InlineQueryResult
 * \brief Create articles to send as inlineQuery result
 * \details Helper class to create articles and pass the results to answerInlineQuery
 */
class InlineQueryResult
{
public:
    /*! \fn InlineQueryResult::InlineQueryResult()
     * \brief InlineQueryResult constructor
     */
    InlineQueryResult();
    short newArticle(const std::string &title,
                     const std::string &message_text,
                     const std::string &description,
                     const Json::Value &reply_markup = Json::Value(),
                     const ParseMode &parse_mode = static_cast<ParseMode>(0),
                     const bool &disable_web_page_preview = true);
    const Json::Value &getResults() const;
private:
    Json::Value results;
    short articleId;
};

}
#endif //CPPGRAM_INLINEQUERYRESULT_H
