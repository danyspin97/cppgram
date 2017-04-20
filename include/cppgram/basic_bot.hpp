#ifndef CPPGRAM_BASIC_BOT_HPP
#define CPPGRAM_BASIC_BOT_HPP

#include <string>
#include <functional>

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>

#include "exception.hpp"
#include "types/update.hpp"

/**
 * \mainpage Reference
 * \section What What is CppGram
 *
 * Cppgram is a wrapper for Telegram Messanger Bot API.
 * Designed to be fast and easy, ensures the developer to build a bot in less
 * time without having to learn Telegram Bot API.
 * The bot class (cppgram::TelegramBot) has a method for each API method, so the
 * only thing you have to do is extend this class and start developing you bot!
 *
 * \subsection Features
 *
 * - Getting udpdates using long or short polling (webhook support coming soon)
 * - Support for the most important API methods
 * - Multithread support
 * - Easy inline keyboard creation
 * - Article creation for inline query
 *
 * \section Install
 *
 * \subsection Requirements
 *
 * This library requires:
 *  - jsoncpp
 *  - cpr, curl
 *  - gcc
 * This wrapper has been tested using g++ version 6.2.1. This wrapper haven't
 * been tested with version below.
 *
 * \subsection Cloning Cloning repository
 *
 * This code will download CppGram, its dependency and will build it:
 *
 *     $ git clone https://gitlab.com/WiseDragonStd/cppgram.git
 *     $ cmake -Hcppgram -Bbuild-cppgram
 *     $ make -C build-cppgram
 *
 * Then link you own bot using:
 *
 *     $ g++ main.cpp lib/*.a -lcurl -o bot -Iinclude -std=c++14 -pthread
 *
 * \section How How to use it
 *
 *     using namespace cppgram;
 *
 *     class MyBot : public TelegramBot {
 *         public:
 *         MyBot() : TelegramBot(TOKEN) {} // Inherit constructor
 *         void processMessage(const message &message) override final {}
 *         void processCallbackQuery(const callbackQuery &callbackQuery)
 * override final {}
 *     };
 *
 *     int main() {
 *         MyBot bot; // Istantiate the bot
 *         bot.run(); // Start getting updates
 *         return 0;
 *     }
 *
 * \subsection processMessage
 *
 * This function will be called everytime your bot receive a message.
 * Override the function adding:
 *
 *     void processMessage(const cppgram::message &message) override;
 *
 * Put here what your bot answer to messages. Parameter message contains all
 * data about the message received.
 *
 * \subsection Inline Keyboards
 *
 * Inline keyboard represent a button below a message.
 * To send a message with a button use this sintax:
 *
 *     // Create the class and add a button
 *     auto keyboard = new InlineKeyboard();
 *     keyboard->addButton("CppGram Documentation",
 * "http://wisedragonstd.gitlab.io/cppgram/", InlineKeyboardButtonType::Url);
 *     // Get the keyboard
 *     string button_string;
 *     keyboard->getKeyboard(button_string);
 *     // Call the api to send a message
 *     sendMessage(chat_id, "Test bot for Cppgram wrapper", button_string);
 *
 * For a complete list of methods check the documentation.
 *
 * \section Compile Compile Options
 *
 * \subsection CMake CMake Configure Options
 *
 * You can configure the project with various options
 *
 *     $ cmake $CPPGRAM_PATH $OPTIONS
 *
 * Availible options are:
 *
 * - -<code>DNOGET_DEPS="yes"/"no" (default: "no"): download dependencies
 * (jsoncpp, cpr)</code>
 * - -<code>DNATIVE="yes"/"no" (default: "no", reccomended: "yes"): build a
 * natively-built static library for your CPU (MAY NOT work on all cpu)</code>
 * - -<code>DARCH=/"-m32"/"-m64" (default: not defined): compile the library in
 * a particulary architecture</code>
 * - -<code>DOPTIMIZATION_LEVEL="2"/"3"/"4"/"fast" (default: not defined,
 * reccomended: "2"): set the compiler optmization</code>
 *
 * Sugggested building options
 *
 *     $ cmake ../cppgram -DCMAKE_CXX_COMPILER="/usr/bin/g++" -DNATIVE="yes"
 * -DOPTIMIZATION_LEVEL="2"
 *
 * \section Extra
 *
 * \subsection Authors
 *
 * This wrapper has been developed by <a
 * href="https://gitlab.com/groups/WiseDragonStd"
 * target="_blank">WiseDragonStd</a> (Danilo Spinella, Stefano Belli).
 *
 * \subsection License
 *
 * This software has been released under the <a
 * href="https://gitlab.com/WiseDragonStd/cppgram/blob/master/LICENSE"
 * target="_blank">GNU LGLPv3</a>.
 *
 *
 */

/**
 * @namespace cppgram
 * @brief main namespace for CppGram
 */
namespace cppgram
{
void
defaultProcessMessage( class BasicBot &bot, const types::Message & );
void
defaultProcessInlineQuery( BasicBot &bot, const types::InlineQuery & );
void
defaultProcessChosenInlineResult( BasicBot &bot, const types::ChosenInlineResult & );
void
defaultProcessCallbackQuery( BasicBot &bot, const types::CallbackQuery & );

/**
 * @brief contains api methods, update handlers and listener
 */
class BasicBot
{
    template <typename T> friend class Polling;

    public:
    /**
     * @brief Constuctor.
     * @param token Bot token. Get a token from [BotFather](https://telegram.me/botfather).
     * @param bot_name Name of the bot (for logging purposes).
     */
    BasicBot( std::string &token, std::string name = "Bot" );

    /**
     * @internal
     * @brief Copy constructor.
     * @param b Bot to copy.
     */
    BasicBot( const BasicBot &b );

    /**
     * @internal
     * @brief Assigment operator.
     * @param b Bot to copy.
     */
    BasicBot operator=( const BasicBot &b );

    /**
     * @brief Get chat_id of the current user/group/channel.
     * @return Chat_id.
     */
    inline std::string getChatID() { return chat_id; }
    /**
     * @brief Set the chat id of the bot.
     * @param chat_id New chat_id to set.
     */
    inline void setChatID( std::string &chat_id ) { this->chat_id = chat_id; }
    /**
     * @see setChatID
     */
    inline void setChatID( uint_fast32_t &chat_id ) { this->chat_id = std::to_string( chat_id ); }
    /**
     * @brief Returns current bot's logger.
     * @return Pointer to the bot's logger.
     */
    std::shared_ptr<spdlog::logger> getLogger() { return logger; }
    /**
     * @brief Set the bot's logger by passing a sink.
     * @details Logger will be automaticcaly created using the sink passed.
     * @param sink Sink of the log to create.
     * @return The logger created.
     */
    std::shared_ptr<spdlog::logger> setLogger( spdlog::sink_ptr sink );

    /**
     * @brief Set the bot's logger by passing a vector of sinks.
     * @details Logger will be automaticcaly created using the sinks passed.
     *
     * @param sinks Sink of the log to create.
     * @return The logger created.
     */
    std::shared_ptr<spdlog::logger> setLogger( std::vector<spdlog::sink_ptr> &sinks );

    /**
     * @brief Set the bot's logger by passing a logger.
     * @param logger New logger to set.
     */
    void setLogger( std::shared_ptr<spdlog::logger> new_logger );

    /**
     * @brief Execute an API method by passing method name and parameters.
     * @details A curl call will be made using cpr::Session of the bot and url generated from API
     * token.
     * @param method Method name.
     * @param params Parameters to pass along with the request.
     * @return The server response.
     */
    const cpr::Response executeRequest( const std::string &method, const cpr::Parameters &params );

    /**
     * @internal
     * @brief parses response's JSON and checks for error codes
     * @param response : the cpr::Response object
     * @param val : the target Json::Value 's reference
     * @return true if everything OK, else: false
     */
    bool checkMethodError( const cpr::Response &response, Json::Value &val );

    /*! \addtogroup Telegram API methods
     * @{
     */

    /**
     * @brief Receive incoming updates using polling (short or long polling based on
     * timeout)
     * @param updates Pushes all the updates on the back of a vector.
     * @param offset Identifier of the first update to be returned. Must be
     * greater by one than the highest among the identifiers of previously
     * received updates. By default, updates starting with the earliest
     * unconfirmed update are returned. An update is considered confirmed as
     * soon as getUpdates is called with an offset higher than its update_id.
     * The negative offset can be specified to retrieve updates starting from
     * -offset update from the end of the updates queue. All previous updates
     * will be forgotten.
     * @param limit Limits the number of updates to be retrieved. Values between
     * 1—100 are accepted.
     * @param timeout Timeout in seconds for long polling.
     * @return True if there are new updates, false otherwise
     */
    bool getUpdates( std::vector<types::Update> &updates,
                     const uint_fast32_t         offset  = 0,
                     const uint_fast32_t         limit   = 100,
                     const uint_fast32_t         timeout = 60 );

    /**
     * @brief Send a message to a specified chat.
     * (https://core.telegram.org/bots/api#sendmessage)
     * @param id Unique identifier for the target chat or username of the target
     * channel (in the format <code>@channelusername</code>)
     * @param text Text of the message to be sent.
     * @param reply_markup Additional interface options. Use InlineKeyboard
     * class to create a reply markup.
     * @param parse_mode Send an enum of type ParseMode.
     * @param disable_web_page_preview Disables link previews for links in this
     * message.
     * @param disable_notification Sends the message silently.
     * @param reply_to_message_id If the message is a reply, ID of the original.
     * message.
     * @return On success, the message sent.
     */
    std::experimental::optional<const class types::Message>
    sendMessage( const std::string &    text,
                 const std::string &    reply_markup             = "",
                 const EParseMode parse_mode               = EParseMode::HTML,
                 const bool             disable_web_page_preview = true,
                 const bool             disable_notification     = false,
                 const int_fast32_t     reply_to_message_id      = 0 );

    /**
     * @brief Use this method to send answers to callback queries sent from inline keyboards. The
     * answer will be displayed to the user as a notification at the top of the chat screen or as an
     * alert.
     * @param text Text of the notification. If not specified, nothing will be shown to the user,
     * 0-200 characters
     * @param show_alert If true, an alert will be shown by the client instead of a notification at
     * the top of the chat screen.
     * @param cache_time The maximum amount of time in seconds that the result of the callback query
     * may be cached client-side.
     * @param URL that will be opened by the user's client. If you have created a Game and accepted
     * the conditions via @Botfather, specify the URL that opens your game – note that this will
     * only work if the query comes from a callback_game button.
     * @return On success, True is returned.
     */
    bool answerCallbackQuery( const std::string &text,
                              bool               show_alert = false,
                              uint32_t           cache_time = 0,
                              const std::string &url        = "" );

    /**
     * @brief Edit text (and reply markup) of a message sent by the bot.
     * @details Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @param chat_id Unique identifier for the target chat or username of the
     * target channel (in the format <code>\@channelusername</code>)
     * @param message_id Unique identifier of the sent message.
     * @param text New text of the message.
     * @param reply_markup Inline keyboard object.
     * @param parse_mode Send an enum of type ParseMode.
     * @param disable_web_page_preview Disables link previews for links in this
     * message.
     * @return On success, the message edited.
     */
    std::experimental::optional<const class types::Message>
    editMessageText( const uint_fast32_t    message_id,
                     const std::string &    text,
                     const std::string &    reply_markup = "",
                     const EParseMode parse_mode   = static_cast<EParseMode>( 1 ),
                     const bool             disable_web_page_preview = true );

    /**
     * @brief Edit text (and reply markup) of a message sent via the bot (using inline
     * queries).
     * @details Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @param inline_message_id Identifier of the inline message.
     * @param text New text of the message.
     * @param reply_markup Inline keyboard object.
     * @param parse_mode Send an enum of type ParseMode.
     * @param disable_web_page_preview Disables link previews for links in this
     * message.
     * @return True on success, false otherwise.
     */
    bool editMessageText( const std::string &    inline_message_id,
                          const std::string &    text,
                          const std::string &    reply_markup = "",
                          const EParseMode parse_mode   = static_cast<EParseMode>( 1 ),
                          const bool             disable_web_page_preview = true );

    /**
     * @brief Edit captions of messages sent by the bot.
     * @details Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagecaption)
     * @param chat_id Unique identifier for the target chat or username of the
     * target channel (in the format <code>\@channelusername</code>).
     * @param caption New caption of the message.
     * @param reply_markup Inline keyboard object.
     * @return On success, the message edited.
     */
    std::experimental::optional<const class types::Message>
    editMessageCaption( const uint_fast32_t message_id,
                        const std::string & caption,
                        const std::string & reply_markup = "" );

    /**
     * @brief Edit captions of messages sent via the bot (using inline_queries).
     * @details Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagecaption)
     * @param inline_message_id Identifier of the inline message.
     * @param caption New caption of the message.
     * @param reply_markup Inline Keyboard object.
     * @return True on success, false otherwise.
     */
    bool editMessageCaption( const std::string &inline_message_id,
                             const std::string &caption,
                             const std::string &reply_markup = "" );

    /**
     * @brief Edit only the reply markup of a message sent by the the bot.
     * @details Leaving reply_markup empty remove it from the message edited.
     * (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @param chat_id Unique identifier for the target chat or username of the
     * target channel (in the format <code>\@channelusername</code>).
     * @param message_id Unique identifier of the sent message.
     * @param reply_markup New inline keyboard object.
     * @return On success, the message edited.
     */
    std::experimental::optional<const class types::Message>
    editMessageReplyMarkup( const uint_fast32_t message_id, const std::string &reply_markup = "" );

    /**
     * Edit only the reply markup of a message sent via the the bot (using
     * inline queries). Leaving reply_markup empty remove it from the message
     * edited. (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @param inline_message_id Identifier of the inline message.
     * @param reply_markup New inline keyboard object.
     * @return True on success, false otherwise.
     */
    bool editMessageReplyMarkup( const std::string &inline_message_id,
                                 const std::string &reply_markup = "" );

    /**
     * @brief Answer an inline query.
     * (https://core.telegram.org/bots/api#answerinlinequery)
     * @param inline_query_id Unique identifier for the answered query
     * @param results JSON serialized array of the results for the inline query.
     * Use InlineQueryResults to create them.
     * @param cache_time The maximum amount of time in seconds that the result
     * of the inline query may be cached on the server.
     * @param is_personal Pass True, if results may be cached on the server side
     * only for the user that sent the query.
     * @param next_offset Pass the offset that a client should send in the next
     * query with the same text to receive more results. Pass an empty string if
     * there are no more results or if you don‘t support pagination.
     * @param switch_pm_text If passed, clients will display a button with
     * specified text that switches the user to a private chat with the bot and.
     * sends the bot a start message with the parameter switch_pm_parameter
     * @param switch_pm_paramter Parameter for the start message sent to the bot
     * when user presses the switch button.
     * @return True on success, false otherwise.
     */
    bool answerInlineQuery( const Json::Value & results,
                            const uint_fast16_t cache_time         = 300,
                            const bool          is_personal        = false,
                            const std::string & next_offset        = "",
                            const std::string & switch_pm_text     = "",
                            const std::string & switch_pm_paramter = "" );

    /** @} */

    /**
     * @addtogroup ProcessUpdates Respond to updates
     * @brief Answer to updates coming from users.
     * @{
     */

    /**
     * @brief Pointer to the function that will be called on each message sent by the user.
     */
    std::function<void ( BasicBot &, const types::Message & )> processMessage = &defaultProcessMessage;

    /**
     * @brief Pointer to the function that will be called on each message edited by the user.
     */
    void ( *processEditedMessage )( BasicBot &, const types::Message & ) = &defaultProcessMessage;

    /**
     * @brief Pointer to the function that will be called on each inline query.
     */
    void ( *processInlineQuery )( BasicBot &, const types::InlineQuery & ) = &defaultProcessInlineQuery;

    /**
     * @brief Pointer to the function that will be called on each inline query choosed by the user.
     */
    void ( *processChosenInlineResult )( BasicBot &, const types::ChosenInlineResult & )
            = &defaultProcessChosenInlineResult;

    /**
     * @brief Pointer to the funciton that will be called on each callback query.
     */
    void ( *processCallbackQuery )( BasicBot &, const types::CallbackQuery & )
            = &defaultProcessCallbackQuery;

    /** @} */

    private:
    /**
     * @internal
     * @brief Forward the update to the functions that will process it.
     * @param Update Update to process.
     */
    void processUpdate( const types::Update &update );

    protected:
    /** @internal @brief Chat_id of the current user/group/channel. */
    std::string chat_id;

    /** @internal @brief ID of the current callback query. */
    std::string callback_query_id;

    /** @internal @brief ID of the current inline query. */
    std::string inline_query_id;

    private:
    /** @internal @brief Json reader. */
    Json::Reader reader;

    /** @internal @brief Connection to API servers. */
    cpr::Session connection;

    /** @internal @brief Logger object. */
    std::shared_ptr<spdlog::logger> logger;

    /** @internal @brief Url endpoint for making requests. */
    std::string api_url,

            /** @internal @brief Name of the bot, for logging purposes. */
            bot_name;
};
}

#endif
