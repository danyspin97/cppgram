#ifndef __CPPGRAM_CORE_BOT_HPP
#define __CPPGRAM_CORE_BOT_HPP

#include "cppgram/exception.hpp"
#include "cppgram/types/message.h"
#include "cppgram/utils.hpp"
#include <cpr/cpr.h>
#include <string>

namespace cppgram
{
class CoreBot
{
    public:
    CoreBot() {}
    std::string getChatID() { return chat_id; }
    void setChatID( std::string &chat_id ) { this.chat_id = chat_id; }
    void setChatID( uint_fast32_t &chat_id ) { this.chat_id = std::tostring( chat_id; ) }
    const cpr::Response executeRequest( const std::string &method, const cpr::Parameters &params )
    {
    }

    /*!
     * \brief parses response's JSON and checks for error codes
     * \param response : the cpr::Response object
     * \param val : the target Json::Value 's reference
     * \return true if everything OK, else: false
     */
    bool checkMethodError( const cpr::Response &response, Json::Value &val )
    {
        static Json::Reader reader;

        // If there was an error in the connection print it
        if ( response.error.code != cpr::ErrorCode::OK )
        {
            log( Log::Error, "HTTP Error:" + response.error.message );
            return false;
        }

        if ( !reader.parse( response.text, val ) )
        {
            log( Log::Error, "JSON Parser: Error while parsing JSON document!" );
            throw cppgram::JsonParseError();
        }

        // Print method error
        if ( response.status_code != 200 )
        {
            log( Log::Error,
                 "Telegram Error: " + val["error_code"].asString() + ", Description: "
                     + val["description"].asString() );
            return false;
        }

        return true;
    }

    /*! \addtogroup Telegram API methods
     * @{
     */

    /**
     * Receive incoming updates using polling (short or long polling based on
     * timeout)
     * @param updates Fill a JSON with the updates received
     * @param offset Identifier of the first update to be returned. Must be
     * greater by one than the highest among the identifiers of previously
     * received updates. By default, updates starting with the earliest
     * unconfirmed update are returned. An update is considered confirmed as
     * soon as getUpdates is called with an offset higher than its update_id.
     * The negative offset can be specified to retrieve updates starting from
     * -offset update from the end of the updates queue. All previous updates
     * will forgotten.
     * @param limit Limits the number of updates to be retrieved. Values between
     * 1—100 are accepted.
     * @param timeout Timeout in seconds for long polling.
     * @return True if there are new updates, false otherwise
     */
    bool getUpdates( Json::Value &       updates,
                     const uint_fast32_t offset  = 0,
                     const uint_fast32_t limit   = 100,
                     const uint_fast32_t timeout = 60 );

    /**
     * Send a message to a specified chat.
     * (https://core.telegram.org/bots/api#sendmessage)
     * @param id Unique identifier for the target chat or username of the target
     * channel (in the format <code>@channelusername</code>)
     * @param text Text of the message to be sent
     * @param reply_markup Additional interface options. Use InlineKeyboard
     * class to create a reply markup
     * @param parse_mode Send an enum of type ParseMode
     * @param disable_web_page_preview Disables link previews for links in this
     * message
     * @param disable_notification Sends the message silently.
     * @param reply_to_message_id If the message is a reply, ID of the original
     * message
     * @return On success, message_id of the message sent, 0 otherwise
     */
    cppgram::message sendMessage( const std::string &      text,
                                  const std::string &      reply_markup = "",
                                  const cppgram::ParseMode parse_mode   = ParseMode::HTML,
                                  const bool               disable_web_page_preview = true,
                                  const bool               disable_notification     = false,
                                  const int_fast32_t       reply_to_message_id      = 0 );

    /**
     * Edit text (and reply markup) of a message sent by the bot. Leaving
     * reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @param chat_id Unique identifier for the target chat or username of the
     * target channel (in the format <code>\@channelusername</code>)
     * @param message_id Unique identifier of the sent message
     * @param text New text of the message
     * @param reply_markup Inline keyboard object
     * @param parse_mode Send an enum of type ParseMode
     * @param disable_web_page_preview Disables link previews for links in this
     * message
     * @return On success, message_id of the message edited, 0 otherwise
     */
    cppgram::message editMessageText( const uint_fast32_t message_id,
                                      const std::string & text,
                                      const std::string & reply_markup = "",
                                      const ParseMode     parse_mode = static_cast<ParseMode>( 1 ),
                                      const bool          disable_web_page_preview = true );

    /**
     * Edit text (and reply markup) of a message sent via the bot (using inline
     * queries). Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @param inline_message_id Identifier of the inline message
     * @param text New text of the message
     * @param reply_markup Inline keyboard object
     * @param parse_mode Send an enum of type ParseMode
     * @param disable_web_page_preview Disables link previews for links in this
     * message
     * @return True on success, false otherwise
     */
    bool editMessageText( const std::string &inline_message_id,
                          const std::string &text,
                          const std::string &reply_markup             = "",
                          const ParseMode    parse_mode               = static_cast<ParseMode>( 1 ),
                          const bool         disable_web_page_preview = true );

    /**
     * Edit captions of messages sent by the bot. Leaving reply_markup empty
     * remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagecaption)
     * @param chat_id Unique identifier for the target chat or username of the
     * target channel (in the format <code>\@channelusername</code>)
     * @param caption New caption of the message
     * @param reply_markup Inline keyboard object
     * @return On success, message_id of the message edited, 0 otherwise
     */
    cppgram::message editMessageCaption( const uint_fast32_t message_id,
                                         const std::string & caption,
                                         const std::string & reply_markup = "" );

    /**
     * Edit captions of messages sent via the bot (using inline_queries).
     * Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagecaption)
     * @param inline_message_id Identifier of the inline message
     * @param caption New caption of the message
     * @param reply_markup Inline Keyboard object
     * @return True on success, false otherwise
     */
    bool editMessageCaption( const std::string &inline_message_id,
                             const std::string &caption,
                             const std::string &reply_markup = "" );

    /**
     * Edit only the reply markup of a message sent by the the bot. Leaving
     * reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @param chat_id Unique identifier for the target chat or username of the
     * target channel (in the format <code>\@channelusername</code>)
     * @param message_id Unique identifier of the sent message
     * @param reply_markup New inline keyboard object
     * @return On success, message_id of the message edited, 0 otherwise
     */
    cppgram::message editMessageReplyMarkup( const uint_fast32_t message_id,
                                             const std::string & reply_markup = "" );

    /**
     * Edit only the reply markup of a message sent via the the bot (using
     * inline queries). Leaving reply_markup empty remove it from the message
     * edited. (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @param inline_message_id Identifier of the inline message
     * @param reply_markup New inline keyboard object
     * @return True on success, false otherwise
     */
    bool editMessageReplyMarkup( const std::string &inline_message_id,
                                 const std::string &reply_markup = "" );

    /**
     * Answer an inline query.
     * (https://core.telegram.org/bots/api#answerinlinequery
     * @param inline_query_id Unique identifier for the answered query
     * @param results JSON serialized array of the results for the inline query.
     * Use InlineQuery to create them
     * @param cache_time The maximum amount of time in seconds that the result
     * of the inline query may be cached on the server
     * @param is_personal Pass True, if results may be cached on the server side
     * only for the user that sent the query
     * @param next_offset Pass the offset that a client should send in the next
     * query with the same text to receive more results. Pass an empty string if
     * there are no more results or if you don‘t support pagination
     * @param switch_pm_text If passed, clients will display a button with
     * specified text that switches the user to a private chat with the bot and
     * sends the bot a start message with the parameter switch_pm_parameter
     * @param switch_pm_paramter Parameter for the start message sent to the bot
     * when user presses the switch button
     * @return True on success, false otherwise
     */
    bool answerInlineQuery( const Json::Value & results,
                            const uint_fast16_t cache_time         = 300,
                            const bool          is_personal        = false,
                            const std::string & next_offset        = "",
                            const std::string & switch_pm_text     = "",
                            const std::string & switch_pm_paramter = "" );

    /** @} */

    protected:
    std::string chat_id;
    std::string callback_query_id;
    std::string inline_query_id;

    private:
    void initCoreBot( std::string &token, cpr::Session &connection );
    const std::string  api_url;
    const cpr::Session connection;
};
}

#endif
