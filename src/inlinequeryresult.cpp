#include <json/json.h>
#include "cppgram/inlinequeryresult.h"
#include "cppgram/structures.h"

using namespace cppgram;
using std::string;
using std::to_string;

InlineQueryResult::InlineQueryResult() : results(Json::Value()), articleId(0)
{}

short InlineQueryResult::newArticle(const string &title,
                                    const string &message_text,
                                    const string &description,
                                    const Json::Value &reply_markup,
                                    const ParseMode &parse_mode,
                                    const bool &disable_web_page_preview)
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
