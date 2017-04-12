// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/basic_bot.hpp"
#include "cppgram/defines.hpp"
#include "cppgram/types/update.hpp"
#include "cppgram/exception.hpp"

using std::string;
using std::thread;
using std::vector;
using std::to_string;

using cppgram::BasicBot;
using cppgram::Update;

using cppgram::Update;
using cppgram::Message;
using cppgram::ParseMode;

using cppgram::JsonParseError;
using cppgram::MessageNotCreated;

BasicBot::BasicBot( string &token ) { api_url = TELEGRAM_API_URL + token + "/"; }
BasicBot::BasicBot( const BasicBot &b )
{
    processMessage            = b.processMessage;
    processEditedMessage      = b.processEditedMessage;
    processInlineQuery        = b.processInlineQuery;
    processChosenInlineResult = b.processChosenInlineResult;
    processCallbackQuery      = b.processCallbackQuery;

    api_url = b.api_url;
}

BasicBot
BasicBot::operator=( const BasicBot &b )
{
    api_url = b.api_url;

    processMessage            = b.processMessage;
    processEditedMessage      = b.processEditedMessage;
    processInlineQuery        = b.processInlineQuery;
    processChosenInlineResult = b.processChosenInlineResult;
    processCallbackQuery      = b.processCallbackQuery;

    sink   = b.sink;
    logger = b.logger;

    return *this;
}

const cpr::Response
BasicBot::executeRequest( const std::string &method, const cpr::Parameters &params )
{
    connection.SetUrl( api_url + method );
    connection.SetParameters( params );
    return connection.Get();
}

bool
BasicBot::checkMethodError( const cpr::Response &response, Json::Value &val )
{
    // If there was an error in the connection print it
    if ( response.error.code != cpr::ErrorCode::OK )
    {
        // log( Log::Error, "HTTP Error:" + response.error.message );
        return false;
    }

    if ( !reader.parse( response.text, val ) )
    {
        // log( Log::Error, "JSON Parser: Error while parsing JSON document!" );
        throw JsonParseError();
    }

    // Print method error
    if ( response.status_code != 200 )
    {
        // log( Log::Error,
        //"Telegram Error: " + val["error_code"].asString() + ", Description: "
        //+ val["description"].asString() );
        return false;
    }

    return true;
}

bool
BasicBot::getUpdates( std::vector<Update> &updates,
                      const uint_fast32_t  offset,
                      const uint_fast32_t  limit,
                      const uint_fast32_t  timeout )
{
    auto response = executeRequest( "getUpdates",
                                    cpr::Parameters{{"timeout", to_string( timeout )},
                                                    {"limit", to_string( limit )},
                                                    {"offset", to_string( offset + 1 )}} );

    Json::Value json_updates;
    if ( !checkMethodError( response, json_updates ) || json_updates["result"].empty() )
    {
        updates = std::vector<Update>();
        return false;
    }

    u_int8_t count = json_updates["result"].size();
    for ( uint8_t i = 0; i != count; ++i )
    {
        updates.push_back( Update( json_updates["result"][i] ) );
    }
    return true;
}

const Message
BasicBot::sendMessage( const std::string &text,
                       const std::string &reply_markup,
                       const ParseMode    parse_mode,
                       const bool         disable_web_page_preview,
                       const bool         disable_notification,
                       const int_fast32_t reply_to_message_id )
{
    std::string parse_mode_string = "";

    if ( parse_mode == ParseMode::HTML )
    {
        parse_mode_string = "HTML";
    }
    else if ( parse_mode == ParseMode::Markdown )
    {
        parse_mode_string = "Markdown";
    }

    auto response = executeRequest(
            "sendMessage",
            cpr::Parameters{{"chat_id", chat_id},
                            {"text", text},
                            {"parse_mode", parse_mode_string},
                            {"disable_web_page_preview", to_string( disable_web_page_preview )},
                            {"disable_notification", to_string( disable_notification )},
                            {"reply_to_message_id", to_string( reply_to_message_id )},
                            {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        throw cppgram::MessageNotCreated();
    }

    return Message( valroot["result"] );
}

const Message
BasicBot::editMessageText( const uint_fast32_t message_id,
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
        throw MessageNotCreated();
    }

    return Message( valroot["result"] );
}

bool
BasicBot::editMessageText( const string &  inline_message_id,
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

const Message
BasicBot::editMessageCaption( const uint_fast32_t message_id,
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
    {
        throw MessageNotCreated();
    }

    return Message( valroot["result"] );
}

bool
BasicBot::editMessageCaption( const string &inline_message_id,
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

const Message
BasicBot::editMessageReplyMarkup( const uint_fast32_t message_id, const string &reply_markup )
{
    auto response = executeRequest( "editMessageReplyMarkup",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", to_string( message_id )},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        throw MessageNotCreated();
    }

    return Message( valroot["result"] );
}

bool
BasicBot::editMessageReplyMarkup( const string &inline_message_id, const string &reply_markup )
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
BasicBot::answerInlineQuery( const Json::Value & results,
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

void
BasicBot::processUpdate( const Update &update )
{
    switch ( update.type )
    {
        case UpdateType::eMessage:
        {
            chat_id = to_string( update.message->chat.id );
            processMessage( *this, std::move( update.message.value() ) );
        }
        break;
        case UpdateType::eCallbackQuery:
        {
            chat_id           = to_string( update.callback_query->message->chat.id );
            callback_query_id = update.callback_query->id;
            processCallbackQuery( *this, std::move( update.callback_query.value() ) );
            callback_query_id = "";
        }
        break;
        case UpdateType::eEditedMessage:
        {
            chat_id = to_string( update.edited_message->chat.id );
            processEditedMessage( *this, std::move( update.edited_message.value() ) );
        }
        break;
        case UpdateType::eInlineQuery:
        {
            chat_id         = to_string( update.inline_query->from.id );
            inline_query_id = update.inline_query->id;
            processInlineQuery( *this, std::move( update.inline_query.value() ) );
            inline_query_id = "";
        }
        break;
        case UpdateType::eChosenInlineResult:
        {
            chat_id = to_string( update.chosen_inline_result->from.id );
            processChosenInlineResult( *this, std::move( update.chosen_inline_result.value() ) );
        }
        break;
        case UpdateType::eChannelPost: break;
        case UpdateType::eEditedChannelPost: break;
    }
}

void
cppgram::defaultProcessMessage( class BasicBot &bot, const Message & )
{
}

void
cppgram::defaultProcessEditedMessage( class BasicBot &bot, const Message & )
{
}

void
cppgram::defaultProcessInlineQuery( class BasicBot &bot, const InlineQuery & )
{
}

void
cppgram::defaultProcessCallbackQuery( class BasicBot &bot, const CallbackQuery & )
{
}

void
cppgram::defaultProcessChosenInlineResult( class BasicBot &bot, const ChosenInlineResult & )
{
}
