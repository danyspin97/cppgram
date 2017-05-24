// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/basic_bot.hpp"
#include "cppgram/commands/command.hpp"
#include "cppgram/exception.hpp"
#include "cppgram/types/update.hpp"

template <class T>
BasicBot<T>::BasicBot( const std::string &token, std::string name, T *obj_ptr )
    : api_url( "https://api.telegram.org/bot" + token + "/" )
    , bot_name( name )
    , logger_ptr( nullptr )
    , command_handler( obj_ptr )
{
}

template <class T> BasicBot<T>::BasicBot( const BasicBot &b, T *base_ptr )
{
    api_url = b.api_url;

    processMessage            = b.processMessage;
    processEditedMessage      = b.processEditedMessage;
    processInlineQuery        = b.processInlineQuery;
    processChosenInlineResult = b.processChosenInlineResult;
    processCallbackQuery      = b.processCallbackQuery;

    bot_name = b.bot_name;

    logger_ptr = b.logger_ptr;

    command_handler = std::move( CommandHandler<T>( base_ptr, b.command_handler ) );
}

template <class T>
BasicBot<T>
BasicBot<T>::operator=( const BasicBot &b )
{
    api_url = b.api_url;

    processMessage            = b.processMessage;
    processEditedMessage      = b.processEditedMessage;
    processInlineQuery        = b.processInlineQuery;
    processChosenInlineResult = b.processChosenInlineResult;
    processCallbackQuery      = b.processCallbackQuery;

    bot_name = b.bot_name;

    logger_ptr = b.logger_ptr;

    // Create a new CommandHandler object, giving this object as owner and the commands of the
    // rvalue, then std::move it in command_handler (to not lose owner ptr)
    command_handler
            = std::move( CommandHandler<T>( dynamic_cast<T *>( this ), b.command_handler ) );

    return *this;
}

template <class T>
std::shared_ptr<spdlog::logger>
BasicBot<T>::setLogger( spdlog::sink_ptr sink )
{
    // Create a vector containing just a single sink
    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back( sink );
    return setLogger( sinks );
}

template <class T>
std::shared_ptr<spdlog::logger>
BasicBot<T>::setLogger( std::vector<spdlog::sink_ptr> &sinks )
{
    try
    {
        // Create a logger to the given sinks
        logger_ptr = std::make_shared<spdlog::logger>( bot_name, sinks.begin(), sinks.end() );

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

template <class T>
void
BasicBot<T>::setLogger( std::shared_ptr<spdlog::logger> new_logger )
{
    logger_ptr = new_logger;
}

template <class T>
void
BasicBot<T>::init()
{
    command_handler.init( dynamic_cast<T *>( this ) );
}

template <class T>
const cpr::Response
BasicBot<T>::executeRequest( const std::string &method, const cpr::Parameters &params )
{
    connection.SetUrl( api_url + method );
    connection.SetParameters( params );
    return connection.Get();
}

template <class T>
bool
BasicBot<T>::checkMethodError( const cpr::Response &response, Json::Value &val )
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

template <class T>
bool
BasicBot<T>::getUpdates( std::vector<Update> &updates,
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
                                    cpr::Parameters{{"timeout", std::to_string( timeout )},
                                                    {"limit", std::to_string( limit )},
                                                    {"offset", std::to_string( offset + 1 )}} );

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

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::sendMessage( const int_fast64_t chat_id,
                          const std::string &text,
                          const std::string &reply_markup,
                          const EParseMode   parse_mode,
                          const bool         disable_web_page_preview,
                          const bool         disable_notification,
                          const int_fast32_t reply_to_message_id )
{
    return sendMessage( std::to_string( chat_id ),
                        text,
                        reply_markup,
                        parse_mode,
                        disable_web_page_preview,
                        disable_notification,
                        reply_to_message_id );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::sendMessage( const std::string &chat_id,
                          const std::string &text,
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
            cpr::Parameters{
                    {"chat_id", chat_id},
                    {"text", text},
                    {"parse_mode", parse_mode_string},
                    {"disable_web_page_preview", std::to_string( disable_web_page_preview )},
                    {"disable_notification", std::to_string( disable_notification )},
                    {"reply_to_message_id", std::to_string( reply_to_message_id )},
                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return cppgram::types::Message();
    }

    return cppgram::types::Message( valroot["result"] );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::sendMessage( const std::string &text,
                          const std::string &reply_markup,
                          const EParseMode   parse_mode,
                          const bool         disable_web_page_preview,
                          const bool         disable_notification,
                          const int_fast32_t reply_to_message_id )
{
    return sendMessage( std::to_string( chat_id ),
                        text,
                        reply_markup,
                        parse_mode,
                        disable_web_page_preview,
                        disable_notification,
                        reply_to_message_id );
}

template <class T>
bool
BasicBot<T>::answerCallbackQuery( const std::string &text,
                                  bool               show_alert,
                                  uint32_t           cache_time,
                                  const std::string &url )
{
    auto response = executeRequest( "answerCallbackQuery",
                                    cpr::Parameters{{"callback_query", callback_query_id},
                                                    {"text", text},
                                                    {"show_alert", std::to_string( show_alert )},
                                                    {"cache_time", std::to_string( cache_time )},
                                                    {"url", url}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return false;
    }

    return true;
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageText( const int_fast64_t  chat_id,
                              const uint_fast32_t message_id,
                              const std::string & text,
                              const std::string & reply_markup,
                              const EParseMode    parse_mode,
                              const bool          disable_web_page_preview )
{
    return sendMessage( std::to_string( chat_id ),
                        message_id,
                        text,
                        reply_markup,
                        parse_mode,
                        disable_web_page_preview );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageText( const std::string & chat_id,
                              const uint_fast32_t message_id,
                              const std::string & text,
                              const std::string & reply_markup,
                              const EParseMode    parse_mode,
                              const bool          disable_web_page_preview )
{
    std::string parseMode = "";

    if ( parse_mode == EParseMode::HTML )
    {
        parseMode = "HTML";
    }
    else if ( parse_mode == EParseMode::Markdown )
    {
        parseMode = "Markdown";
    }

    auto response = executeRequest( "editMessageText",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", std::to_string( message_id )},
                                                    {"text", text},
                                                    {"parse_mode", parseMode},
                                                    {"disable_web_page_preview",
                                                     std::to_string( disable_web_page_preview )},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return cppgram::types::Message();
    }

    return cppgram::types::Message( valroot["result"] );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageText( const uint_fast32_t message_id,
                              const std::string & text,
                              const std::string & reply_markup,
                              const EParseMode    parse_mode,
                              const bool          disable_web_page_preview )
{
    return editMessageText( std::to_string( chat_id ),
                            message_id,
                            text,
                            reply_markup,
                            parse_mode,
                            disable_web_page_preview );
}

template <class T>
bool
BasicBot<T>::editMessageText( const std::string &inline_message_id,
                              const std::string &text,
                              const std::string &reply_markup,
                              const EParseMode   parse_mode,
                              const bool         disable_web_page_preview )
{
    std::string parseMode = "";

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

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageCaption( const int_fast64_t  chat_id,
                                 const uint_fast32_t message_id,
                                 const std::string & caption,
                                 const std::string & reply_markup )
{
    return editMessageCaption( std::to_string( chat_id ), message_id, caption, reply_markup );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageCaption( const std::string & chat_id,
                                 const uint_fast32_t message_id,
                                 const std::string & caption,
                                 const std::string & reply_markup )
{
    auto response = executeRequest( "editMessageCaption",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", std::to_string( message_id )},
                                                    {"caption", caption},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return cppgram::types::Message();
    }

    return cppgram::types::Message( valroot["result"] );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageCaption( const uint_fast32_t message_id,
                                 const std::string & caption,
                                 const std::string & reply_markup )
{
    return editMessageCaption( std::to_string( chat_id ), message_id, caption, reply_markup );
}

template <class T>
bool
BasicBot<T>::editMessageCaption( const std::string &inline_message_id,
                                 const std::string &caption,
                                 const std::string &reply_markup )
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

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageReplyMarkup( const int_fast64_t  chat_id,
                                     const uint_fast32_t message_id,
                                     const std::string & reply_markup )
{
    return editMessageReplyMarkup( std::to_string( chat_id ), message_id, reply_markup );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageReplyMarkup( const std::string & chat_id,
                                     const uint_fast32_t message_id,
                                     const std::string & reply_markup )
{
    auto response = executeRequest( "editMessageReplyMarkup",
                                    cpr::Parameters{{"chat_id", chat_id},
                                                    {"message_id", std::to_string( message_id )},
                                                    {"reply_markup", reply_markup}} );

    Json::Value valroot;
    if ( !checkMethodError( response, valroot ) )
    {
        return cppgram::types::Message();
    }

    return cppgram::types::Message( valroot["result"] );
}

template <class T>
std::experimental::optional<const cppgram::types::Message>
BasicBot<T>::editMessageReplyMarkup( const uint_fast32_t message_id,
                                     const std::string & reply_markup )
{
    return editMessageReplyMarkup( std::to_string( chat_id ), message_id, reply_markup );
}

template <class T>
bool
BasicBot<T>::editMessageReplyMarkup( const std::string &inline_message_id,
                                     const std::string &reply_markup )
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

template <class T>
bool
BasicBot<T>::answerInlineQuery( const Json::Value & results,
                                const uint_fast16_t cache_time,
                                const bool          is_personal,
                                const std::string & next_offset,
                                const std::string & switch_pm_text,
                                const std::string & switch_pm_paramter )
{
    Json::FastWriter writer;

    auto response = executeRequest( "answerInlineQuery",
                                    cpr::Parameters{{"inline_query_id", inline_query_id},
                                                    {"results", writer.write( results )},
                                                    {"cache_time", std::to_string( cache_time )},
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

template <class T>
void
BasicBot<T>::processUpdate( const Update &update )
{
    if ( command_handler.processCommands( update ) )
    {
        return;
    }

    T &bot = dynamic_cast<T &>( *this );
    switch ( update.type )
    {
        case EUpdate::eMessage:
        {
            if ( processMessage )
            {
                chat_id = update.message->chat.id;
                processMessage( bot, std::move( update.message.value() ) );
            }
        }
        break;
        case EUpdate::eCallbackQuery:
        {
            chat_id           = update.callback_query->message->chat.id;
            callback_query_id = update.callback_query->id;
            processCallbackQuery( bot, std::move( update.callback_query.value() ) );
            callback_query_id = "";
        }
        break;
        case EUpdate::eEditedMessage:
        {
            if ( processEditedMessage )
            {
                chat_id = update.message->chat.id;
                processEditedMessage( bot, std::move( update.message.value() ) );
            }
        }
        break;
        case EUpdate::eInlineQuery:
        {
            chat_id         = update.inline_query->from.id;
            inline_query_id = update.inline_query->id;
            processInlineQuery( bot, std::move( update.inline_query.value() ) );
            inline_query_id = "";
        }
        break;
        case EUpdate::eChosenInlineResult:
        {
            chat_id = update.chosen_inline_result->from.id;
            processChosenInlineResult( bot, std::move( update.chosen_inline_result.value() ) );
        }
        break;
        case EUpdate::eChannelPost:
        {
            chat_id = update.message->chat.id;
            processChannelPost( bot, std::move( update.message.value() ) );
        }
        break;
        case EUpdate::eEditedChannelPost:
        {
            chat_id = update.message->chat.id;
            processEditedChannelPost( bot, std::move( update.message.value() ) );
        }
        break;
    }
}
