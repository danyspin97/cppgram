#include "cppgram/core_bot.hpp"

using std::string;
using std::to_string;

using cppgram::CoreBot;
using cppgram::Message;
using cppgram::ParseMode;

bool
CoreBot::getUpdates( Json::Value &       updates,
                     const uint_fast32_t offset,
                     const uint_fast32_t limit,
                     const uint_fast32_t timeout )
{
    auto response = executeRequest( "getUpdates",
                                    cpr::Parameters{{"timeout", to_string( timeout )},
                                                    {"limit", to_string( limit )},
                                                    {"offset", to_string( offset + 1 )}} );

    if ( !checkMethodError( response, updates ) )
    {
        return false;
    }

    if ( updates["result"].empty() )
    {
        return false;
    }
    else
    {
        return true;
    }
}

Message
CoreBot::sendMessage( const std::string &text,
                      const std::string &reply_markup,
                      const ParseMode    parse_mode,
                      const bool         disable_web_page_preview,
                      const bool         disable_notification,
                      const int_fast32_t reply_to_message_id )
{
    std::string parseMode = "";

    if ( parse_mode == ParseMode::HTML )
    {
        parseMode = "HTML";
    }
    else if ( parse_mode == ParseMode::Markdown )
    {
        parseMode = "Markdown";
    }

    auto response = executeRequest(
            "sendMessage",
            cpr::Parameters{{"chat_id", chat_id},
                            {"text", text},
                            {"parse_mode", parseMode},
                            {"disable_web_page_preview", to_string( disable_web_page_preview )},
                            {"disable_notification", to_string( disable_notification )},
                            {"reply_to_message_id", to_string( reply_to_message_id )},
                            {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return Message();
    }

    return Message( valroot["result"] );
}

Message
CoreBot::editMessageText( const uint_fast32_t message_id,
                          const string &      text,
                          const string &      reply_markup,
                          const ParseMode     parse_mode,
                          const bool          disable_web_page_preview )
{
    string parseMode = "";

    if ( parse_mode == ParseMode::HTML )
    {
        parseMode = "HTML";
    }
    else if ( parse_mode == ParseMode::Markdown )
    {
        parseMode = "Markdown";
    }

    auto response = executeRequest(
            "editMessageText",
            cpr::Parameters{{"chat_id", chat_id},
                            {"message_id", to_string( message_id )},
                            {"text", text},
                            {"parse_mode", parseMode},
                            {"disable_web_page_preview", to_string( disable_web_page_preview )},
                            {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return Message();
    }

    return Message( valroot["result"] );
}

bool
CoreBot::editMessageText( const string &  inline_message_id,
                          const string &  text,
                          const string &  reply_markup,
                          const ParseMode parse_mode,
                          const bool      disable_web_page_preview )
{
    string parseMode = "";

    if ( parse_mode == ParseMode::HTML )
    {
        parseMode = "HTML";
    }
    else if ( parse_mode == ParseMode::Markdown )
    {
        parseMode = "Markdown";
    }

    auto response = executeRequest(
            "editMessageText",
            cpr::Parameters{{"inline_message_id", inline_message_id},
                            {"text", text},
                            {"parse_mode", parseMode},
                            {"disable_web_page_preview", disable_web_page_preview},
                            {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return false;
    }

    return valroot["result"].asBool();
}

Message
CoreBot::editMessageCaption( const uint_fast32_t message_id,
                             const string &      caption,
                             const string &      reply_markup )
{
    auto response = executeRequest( "editMessageCaption",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", to_string( message_id )},
                                                    {"caption", caption},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
        return Message();

    return Message( valroot["result"] );
}

bool
CoreBot::editMessageCaption( const string &inline_message_id,
                             const string &caption,
                             const string &reply_markup )
{
    auto response = executeRequest( "editMessageCaption",
                                    cpr::Parameters{{"inline_message_id", inline_message_id},
                                                    {"caption", caption},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return false;
    }

    return valroot["result"].asBool();
}

Message
CoreBot::editMessageReplyMarkup( const uint_fast32_t message_id, const string &reply_markup )
{
    auto response = executeRequest( "editMessageReplyMarkup",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", to_string( message_id )},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
        return Message();

    return Message( valroot["result"] );
}

bool
CoreBot::editMessageReplyMarkup( const string &inline_message_id, const string &reply_markup )
{
    auto response = executeRequest( "editMessageReplyMarkup",
                                    cpr::Parameters{{"inline_message_id", inline_message_id},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return false;
    }

    return valroot["result"].asBool();
}

bool
CoreBot::answerInlineQuery( const Json::Value & results,
                            const uint_fast16_t cache_time,
                            const bool          is_personal,
                            const string &      next_offset,
                            const string &      switch_pm_text,
                            const string &      switch_pm_paramter )
{
    Json::FastWriter writer;

    auto response = executeRequest( "answerInlineQuery",
                                    cpr::Parameters{{"inline_query_id", inline_query_id},
                                                    {"results", writer.write( results )},
                                                    {"cache_time", to_string( cache_time )},
                                                    {"is_personal", is_personal},
                                                    {"next_offset", next_offset},
                                                    {"switch_pm_text", switch_pm_paramter},
                                                    {"switch_pm_parameter", switch_pm_paramter}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return false;
    }

    return valroot["result"].asBool();
}
