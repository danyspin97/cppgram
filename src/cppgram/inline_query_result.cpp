// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <vector>

#include <json/json.h>

#include "cppgram/inline_query_result.hpp"
#include "cppgram/types/update.hpp"


using namespace cppgram;
using std::string;
using std::to_string;

InlineQueryResult::InlineQueryResult()
    : results( Json::Value() )
    , articleId( 0 )
{
}

short
InlineQueryResult::newArticle( const std::string &title,
                               const std::string &message_text,
                               const Json::Value &reply_markup,
                               const std::string &description,
                               const ParseMode    parse_mode,
                               const bool         disable_web_page_preview )
{
    string mode = "";
    if ( parse_mode == ParseMode::HTML )
    {
        mode = "HTML";
    }
    else if ( parse_mode == ParseMode::Markdown )
    {
        mode = "markdown";
    }

    results[articleId]["type"]         = Json::StaticString( "article" );
    results[articleId]["id"]           = to_string( articleId );
    results[articleId]["title"]        = title;
    results[articleId]["message_text"] = message_text;
    results[articleId]["description"]  = description;
    results[articleId]["parse_mode"]   = mode;

    // TODO Deep copy of reply_markup
    /*if (!reply_markup.empty())
    {
        const char *mystr[] = {"callback_data", "url", "switch_inline_query"};

        int i = 0;
        for (const Json::Value &button : reply_markup["inline_keyboard"])
        {
            for (int k = 2; k != 0; k--)
                if (!button[mystr[k]].isNull())
                    results[articleId]["reply_markup"]["inline_keyboard"][i][mystr[k]];

            results[articleId]["reply_markup"]["inline_keyboard"][i]["text"] =
    button["text"];
            int k = 2;

            while (k > 0 &&
    !reply_markup["inline_keyboard"][i].isMember(mystr[i]))
                k--;

            results[articleId]["reply_markup"]["inline_keyboard"][mystr[k]] =
    reply_markup["inline_keyboard"][i][mystr[k]];

            results[articleId]["reply_markup"]["inline_keyboard"][i]["text"] =
    reply_markup["inline_keyboard"][i]["text"];
            std::cout<<mystr[k]<<std::endl;


            i++;
        }

    }*/
    if ( !reply_markup.empty() )
    {
        results[articleId]["reply_markup"] = reply_markup;
    }

    results[articleId]["disable_web_page_preview"] = disable_web_page_preview;

    articleId++;

    return articleId;
}

const Json::Value &
InlineQueryResult::getResults() const
{
    return results;
}
