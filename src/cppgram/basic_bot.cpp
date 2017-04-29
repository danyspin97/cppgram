// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/basic_bot.hpp"
#include "cppgram/commands/command.hpp"
#include "cppgram/exception.hpp"
#include "cppgram/types/update.hpp"

using std::string;
using std::to_string;

using std::vector;
using std::move;
using std::experimental::optional;

using std::shared_ptr;
using std::make_shared;

using cppgram::BasicBot;
using cppgram::CommandHandler;

using cppgram::types::Update;
using cppgram::types::Message;
using cppgram::types::CallbackQuery;
using cppgram::types::InlineQuery;
using cppgram::types::ChosenInlineResult;

using cppgram::EParseMode;
using cppgram::EUpdate;

using cppgram::JsonParseError;

BasicBot::BasicBot( string &token, string name )
    : api_url( "https://api.telegram.org/bot" + token + "/" )
    , bot_name( name )
    , logger_ptr( nullptr )
    , command_handler( this )
{
}

BasicBot::BasicBot( const BasicBot &b )
    : command_handler( CommandHandler( this, b.command_handler ) )
{
    api_url = b.api_url;

    processMessage            = b.processMessage;
    processEditedMessage      = b.processEditedMessage;
    processInlineQuery        = b.processInlineQuery;
    processChosenInlineResult = b.processChosenInlineResult;
    processCallbackQuery      = b.processCallbackQuery;

    bot_name = b.bot_name;

    logger_ptr = b.logger_ptr;
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

    bot_name = b.bot_name;

    logger_ptr = b.logger_ptr;

    command_handler = CommandHandler( this, b.command_handler );

    return *this;
}

shared_ptr<spdlog::logger>
BasicBot::setLogger( spdlog::sink_ptr sink )
{
    // Create a vector containing just a single sink
    vector<spdlog::sink_ptr> sinks;
    sinks.push_back( sink );
    return setLogger( sinks );
}

shared_ptr<spdlog::logger>
BasicBot::setLogger( vector<spdlog::sink_ptr> &sinks )
{
    try
    {
        // Create a logger to the given sinks
        logger_ptr = make_shared<spdlog::logger>( bot_name, sinks.begin(), sinks.end() );

        // Flush on error or severe messages
        logger_ptr->flush_on( spdlog::level::err );

        // Return created logger
        return logger_ptr;
    }
    catch ( const spdlog::spdlog_ex &ex )
    {
        // catch the error
        auto console = spdlog::get( "error_console" );
        console->error( ex.what() );
    }

    // We could not create a logger, return a nullptr
    return nullptr;
}

void
BasicBot::setLogger( std::shared_ptr<spdlog::logger> new_logger )
{
    logger_ptr = new_logger;
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
        logger_ptr->error( "HTTP Error:" + response.error.message );
        return false;
    }

    if ( !reader.parse( response.text, val ) )
    {
        logger_ptr->error( "JSON Parser: Error while parsing JSON document!" );
        throw JsonParseError();
    }

    // Print method error
    if ( response.status_code != 200 )
    {
        logger_ptr->error( "Telegram Error: " + val["error_code"].asString() + ", Description: "
                           + val["description"].asString() );
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
    // If there are items in the vector
    if ( updates.size() != 0 )
    {
        // clear it
        updates.clear();
    }

    auto response = executeRequest( "getUpdates",
                                    cpr::Parameters{{"timeout", to_string( timeout )},
                                                    {"limit", to_string( limit )},
                                                    {"offset", to_string( offset + 1 )}} );

    Json::Value json_updates;
    if ( !checkMethodError( response, json_updates ) || json_updates["result"].empty() )
    {
        return false;
    }

    // For each update
    for ( auto &json_single_update : json_updates["result"] )
    {
        // Construct them in place
        updates.emplace_back( json_single_update );
    }

    // We found updates
    return true;
}

optional<const Message>
BasicBot::sendMessage( const std::string &text,
                       const std::string &reply_markup,
                       const EParseMode   parse_mode,
                       const bool         disable_web_page_preview,
                       const bool         disable_notification,
                       const int_fast32_t reply_to_message_id )
{
    std::string parse_mode_string = "";

    if ( parse_mode == EParseMode::HTML )
    {
        parse_mode_string = "HTML";
    }
    else if ( parse_mode == EParseMode::Markdown )
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
        return Message();
    }

    return Message( valroot["result"] );
}

bool
BasicBot::answerCallbackQuery( const std::string &text,
                               bool               show_alert,
                               uint32_t           cache_time,
                               const std::string &url )
{
    auto response = executeRequest( "answerCallbackQuery",
                                    cpr::Parameters{{"callback_query", callback_query_id},
                                                    {"text", text},
                                                    {"show_alert", to_string( show_alert )},
                                                    {"cache_time", to_string( cache_time )},
                                                    {"url", url}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return false;
    }

    return true;
}

optional<const Message>
BasicBot::editMessageText( const uint_fast32_t message_id,
                           const string &      text,
                           const string &      reply_markup,
                           const EParseMode    parse_mode,
                           const bool          disable_web_page_preview )
{
    string parseMode = "";

    if ( parse_mode == EParseMode::HTML )
    {
        parseMode = "HTML";
    }
    else if ( parse_mode == EParseMode::Markdown )
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
BasicBot::editMessageText( const string &   inline_message_id,
                           const string &   text,
                           const string &   reply_markup,
                           const EParseMode parse_mode,
                           const bool       disable_web_page_preview )
{
    string parseMode = "";

    if ( parse_mode == EParseMode::HTML )
    {
        parseMode = "HTML";
    }
    else if ( parse_mode == EParseMode::Markdown )
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

optional<const Message>
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
        return Message();
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

optional<const Message>
BasicBot::editMessageReplyMarkup( const uint_fast32_t message_id, const string &reply_markup )
{
    auto response = executeRequest( "editMessageReplyMarkup",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", to_string( message_id )},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return Message();
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
    if ( command_handler.processCommands( update ) )
    {
        return;
    }

    switch ( update.type )
    {
        case EUpdate::eMessage:
        {
            chat_id = to_string( update.message->chat.id );
            processMessage( *this, move( update.message.value() ) );
        }
        break;
        case EUpdate::eCallbackQuery:
        {
            chat_id           = to_string( update.callback_query->message->chat.id );
            callback_query_id = update.callback_query->id;
            processCallbackQuery( *this, move( update.callback_query.value() ) );
            callback_query_id = "";
        }
        break;
        case EUpdate::eEditedMessage:
        {
            chat_id = to_string( update.message->chat.id );
            processEditedMessage( *this, move( update.message.value() ) );
        }
        break;
        case EUpdate::eInlineQuery:
        {
            chat_id         = to_string( update.inline_query->from.id );
            inline_query_id = update.inline_query->id;
            processInlineQuery( *this, move( update.inline_query.value() ) );
            inline_query_id = "";
        }
        break;
        case EUpdate::eChosenInlineResult:
        {
            chat_id = to_string( update.chosen_inline_result->from.id );
            processChosenInlineResult( *this, move( update.chosen_inline_result.value() ) );
        }
        break;
        case EUpdate::eChannelPost:
        {
            chat_id = to_string( update.message->chat.id );
            processChannelPost( *this, move( update.message.value() ) );
        }
        break;
        case EUpdate::eEditedChannelPost:
        {
            chat_id = to_string( update.message->chat.id );
            processEditedChannelPost( *this, move( update.message.value() ) );
        }
        break;
    }
}

void
cppgram::defaultProcessMessage( class BasicBot &bot, const Message & )
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
