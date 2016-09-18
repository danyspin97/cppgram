#include <json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;
using namespace std;

InlineQueryResult::InlineQueryResult()
{
    results = Json::Value();
    articleId = 0;
}

short InlineQueryResult::newArticle(const std::string &title,
                                    const std::string &message_text,
                                    const std::string &description,
                                    const Json::Value &reply_markup,
                                    ParseMode parse_mode,
                                    bool disable_web_page_preview)
{
    string mode = "";
    if (parse_mode == ParseMode::HTML)
        mode = "HTML";
    else if (parse_mode == ParseMode::Markdown)
        mode = "markdown";

    results[articleId]["type"] = Json::StaticString("article");
    results[articleId]["id"] = to_string(articleId);
    results[articleId]["title"] = title;
    results[articleId]["message_text"] = message_text;
    results[articleId]["description"] = description;
    results[articleId]["parse_mode"] = mode;
    results[articleId]["reply_markup"].append(reply_markup);
    results[articleId]["disable_web_page_preview"] = disable_web_page_preview;

    articleId++;

    return articleId;
}

const Json::Value& InlineQueryResult::getResults()
{
    return results;
}
