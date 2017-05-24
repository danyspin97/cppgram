#ifndef CPPGRAM_BASIC_BOT_HPP
#define CPPGRAM_BASIC_BOT_HPP

#include <string>

#include <cpr/cpr.h>
#include <spdlog/spdlog.h>

#include "command_handler.hpp"
#include "exception.hpp"
#include "keyboard.hpp"
#include "types/update.hpp"

/**
 * \mainpage Reference
 * \section What What is Cppgram
 *
 * Cppgram is a lighweight framework for Telegram Bot API that provides support for the most
 * important api methods and basic features a user need, ensuring speed and stability.
 *
 * \subsection Usage
 *
 *     // Include the framework
 *     #include "cppgram/cppgram.hpp"
 *
 *     // Create your custom Bot class
 *     class MyBot : public cppgram::BasicBot<MyBot> {
 *         public:
 *         MyBot(string &token) : BasicBot(token, "MyBotName", this) {}
 *
 *         MyBot(const MyBot &b) : BasicBot(b, this) {}
 *     };
 *
 *     // Answer all messages received
 *     void helloWorld(MyBot &bot,
 *                 const cppgram::types::Message &message) {
 *
 *         // sending a "Hello World" message
 *         bot.sendMessage("Hello World");
 *     }
 *
 *     int main() {
 *         std::string token = "token";
 *         auto bot = MyBot(token);
 *         // Say the bot to answer all messages using our Hello World function
 *         bot.processMessage = &helloWorld;
 *         // Create a poll with 8 thread running
 *         auto poll = cppgram::Polling<MyBot>(bot, 8);
 *         poll.run();
 *     }
 *
 * \subsection Features
 *
 * - Easy to use
 * - Receive updates using getUpdates
 * - Use multithreading to process updates
 * - A container for each telegram type
 * - Commands support
 * - Create inline keyboard
 * - Create inline query
 * - Use curl session to avoid re-connecting
 * - Log warnings and errors
 *
 * \section Install
 * To start using this library you can fork [this
 * repository](https://github.com/DanySpin97/cppgram-example). It is an example project configured
 * with
 * the minimal boilerplate you need to make this library works.
 *
 * If you already have a project you can include this library using git submodules:
 *
 *     git submodule add git://github.com/DanySpin97/cppgram.git
 *     git submodule update --init --recursive
 *
 * Then add the directory in your cmake configuration:
 *
 *     add_subdirectory(cppgram)
 *
 * Cppgram will be compiled, headers and libraries needs to be included by the project:
 *
 *     include_directories(${CPPGRAM_INCLUDE_DIRS})
 *     target_link_libraries( your_target_name ${CPPGRAM_LIBRARIES})
 *
 * \section How How to use it
 *
 * \subsection Answer all messages
 * Create a method that take a class derived from <code>cppgram::BasicBot</code> and a
 * <code>cppgram::types::Message</code> as argument:
 *
 *     void processMessage(MyBot& bot, cppgram::types::Message);
 *
 * Then say the bot to use this funciton to process all messages received:
 *
 *     bot.processMessage = &processMessage;
 *
 * All the message received will be forwarded to this function.
 * To each update type a different function pointer is called:
 *
 * - cppgram::BasicBot::processMessage -> message
 * - cppgram::BasicBot::processEditedMessage -> edited_message
 * - cppgram::BasicBot::processChannelPost -> channel_post
 * - cppgram::BasicBot::processEditedChannelPost -> edited_channel_post
 * - cppgram::BasicBot::processInlineQuery -> inline_query
 * - cppgram::BasicBot::processChosenInlineResult -> chosen_inline_result
 * - cppgram::BasicBot::processCallbackQuery -> callback_query
 *
 * Check the [bot API reference](https://core.telegram.org/bots/api#update) for more information.
 *
 * \section Commands
 * Cppgram support commands, as of version 1.0.
 *
 * Commands are entities that have special conditions and they're called only if an update meet
 * them.
 *
 * The validation check is done before the pointers listed above. If no command has been triggered,
 * the bot will use the processUpdates pointers.
 *
 * \subsection MessageCommand Message Commands
 * cppgram::commands::MessageCommand are commands triggered when a message contains a
 * [MessageEntity](https://core.telegram.org/bots/api#messageentity) of type
 * <code>bot_command</code> as first part of the text.
 *
 * If you want to put a greeting for user that click /start on the bot using MessageCommand:
 *
 *
 *     // Define the function that will be called on each "/start" message received
 *     void startCommand(MyBot &bot,
 *                    const cppgram::types::Message &message) {
 *         bot.sendMessage("This is a start message");
 *     }
 *
 *     int main() {
 *         // Create the bot
 *         ...
 *
 *         // The string that has to appear in the bot_command
 *         // Do not include the "/"
 *         std::string command_name = "start";
 *
 *         // Create the command
 *         cppgram::commands::MessageCommand *command =
 *                 // passing the command name and the function pointer
 *                 new cppgram::commands::MessageCommand<MyBot>(command_name, &startCommand);
 *
 *         // Add it to the command handler
 *         bot.commands().addCommand(command);
 *
 *         // Run the bot
 *         ...
 *     }
 *
 * \section InlineKeyboards Inline Keyboards
 *
 * Inline keyboard represent a button below a message.
 * To send a message with a button use this sintax:
 *
 *     // Create a button
 *     bot.keyboard().addButton("Cppgram Documentation",
 *             "http://DanySpin97.github.io/cppgram/", InlineKeyboardButtonType::Url);
 *
 *     // Get the keyboard JSON decoded to send it to telegram
 *     string button_string;
 *     keyboard.getKeyboard(button_string);
 *
 *     // Call the api to send a message
 *     sendMessage(chat_id, "Test bot for Cppgram wrapper", button_string);
 *
 * For a complete list of methods check the documentation about cppgram::Keyboard.
 *
 * \section Compile Compile Options
 *
 * \section About
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
 * @brief main namespace for Cppgram
 */
namespace cppgram
{
/**
 * @brief contains api methods, update handlers and listener.
 * @details The basic bot that contains all basic features.
 */
template <class T> class BasicBot
{
    template <typename V> friend class Polling;
    template <class Z> friend class commands::Command;

    public:
    /**
     * @brief Constuctor.
     * @param token Bot token. Get a token from [BotFather](https://telegram.me/botfather).
     * @param bot_name Name of the bot (for logging purposes).
     * @param obj_ptr Pointer to this object.
     * Cannot use "this" keyboard in costructor as this is not the final object.
     * Pointer to the derived class that is calling this parent constructor.
     */
    BasicBot( const std::string &token, std::string name = "Bot", T *obj_ptr = nullptr );

    /**
     * @brief Copy constructor.
     * @param b Bot to copy.
     */
    BasicBot( const BasicBot &b, T *base_ptr );

    virtual ~BasicBot() {}

    /**
     * @internal
     * @brief Assigment operator.
     * @param b Bot to copy.
     */
    BasicBot operator=( const BasicBot &b );

    /**
     * @brief Set the chat id of the bot.
     * @param chat_id New chat_id to set.
     */
    inline void setChatId( uint_fast32_t chat_id ) { this->chat_id = chat_id; }

    /**
     * @brief Set the chat id of the bot.
     * @see setChatId
     */
    inline void setChatId( int_fast64_t chat_id ) { this->chat_id = chat_id; }

    /**
     * @brief Get command handler object.
     * @return Reference to the object.
     * */
    inline CommandHandler<T> &commands() { return command_handler; }

    /**
     * @brief Get the keyboard handler.
     * @return Reference to the object.
     */
    inline Keyboard &keyboard() { return keyboard_obj; }

    /**
     * @brief Returns current bot's logger.
     * @return Pointer to the bot's logger.
     */
    inline std::shared_ptr<spdlog::logger> logger() { return logger_ptr; }

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
    inline std::shared_ptr<spdlog::logger> setLogger( std::vector<spdlog::sink_ptr> &sinks );

    /**
     * @brief Set the bot's logger by passing a logger.
     * @param logger New logger to set.
     */
    void setLogger( std::shared_ptr<spdlog::logger> new_logger );

    /**
     * @brief Init bot object.
     */
    virtual void init();

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
     * @param chat_id Unique identifier for the target chat.
     * @param text Text of the message to be sent.
     * @param reply_markup Additional interface options. Use InlineKeyboard
     * class to create a reply markup.
     * @param parse_mode Send an enum of type ParseMode.
     * @param disable_web_page_preview Disables link previews for links in this
     * message.
     * @param disable_notification Sends the message silently.
     * @param reply_to_message_id If the message is a reply, Id of the original.
     * message.
     * @return On success, the message sent.
     */
    std::experimental::optional<const class types::Message>
    sendMessage( const int_fast64_t chat_id,
                 const std::string &text,
                 const std::string &reply_markup             = "",
                 const EParseMode   parse_mode               = EParseMode::HTML,
                 const bool         disable_web_page_preview = true,
                 const bool         disable_notification     = false,
                 const int_fast32_t reply_to_message_id      = 0 );

    /**
     * @brief Send a message to a specified chat.
     * (https://core.telegram.org/bots/api#sendmessage)
     * @see sendMessage
     */
    std::experimental::optional<const class types::Message>
    sendMessage( const std::string &chat_id,
                 const std::string &text,
                 const std::string &reply_markup             = "",
                 const EParseMode   parse_mode               = EParseMode::HTML,
                 const bool         disable_web_page_preview = true,
                 const bool         disable_notification     = false,
                 const int_fast32_t reply_to_message_id      = 0 );

    /**
     * @brief Send a message to a specified chat.
     * @param chat_id Username of the target channel or group (in the format
     * <code>\@channelusername</code>).
     * (https://core.telegram.org/bots/api#sendmessage)
     * @see sendMessage
     */
    std::experimental::optional<const class types::Message>
    sendMessage( const std::string &text,
                 const std::string &reply_markup             = "",
                 const EParseMode   parse_mode               = EParseMode::HTML,
                 const bool         disable_web_page_preview = true,
                 const bool         disable_notification     = false,
                 const int_fast32_t reply_to_message_id      = 0 );

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
     * @details Leaving reply_markup empty remove it from the edited message.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @param chat_id Unique identifier for the target chat.
     * @param message_id Unique identifier of the sent message.
     * @param text New text of the message.
     * @param reply_markup Inline keyboard object.
     * @param parse_mode Send an enum of type ParseMode.
     * @param disable_web_page_preview Disables link previews for links in this
     * message.
     * @return On success, the edited message.
     */
    std::experimental::optional<const class types::Message>
    editMessageText( const int_fast64_t  chat_id,
                     const uint_fast32_t message_id,
                     const std::string & text,
                     const std::string & reply_markup             = "",
                     const EParseMode    parse_mode               = static_cast<EParseMode>( 1 ),
                     const bool          disable_web_page_preview = true );

    /**
     * @brief Edit text (and reply markup) of a message sent by the bot.
     * @param chat_id Username of the target channel or group (in the format
     * <code>\@channelusername</code>).
     * @see editMessageText
     */
    std::experimental::optional<const class types::Message>
    editMessageText( const std::string & chat_id,
                     const uint_fast32_t message_id,
                     const std::string & text,
                     const std::string & reply_markup             = "",
                     const EParseMode    parse_mode               = static_cast<EParseMode>( 1 ),
                     const bool          disable_web_page_preview = true );

    /**
     * @brief Edit text (and reply markup) of a message sent by the bot.
     * @details The chat selected will be the chat from where the current update was received.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @see editMessageText
     */
    std::experimental::optional<const class types::Message>
    editMessageText( const uint_fast32_t message_id,
                     const std::string & text,
                     const std::string & reply_markup             = "",
                     const EParseMode    parse_mode               = static_cast<EParseMode>( 1 ),
                     const bool          disable_web_page_preview = true );
    /**
     * @brief Edit text (and reply markup) of a message sent via the bot (using inline
     * queries).
     * @details Leaving reply_markup empty remove it from the edited message.
     * (https://core.telegram.org/bots/api#editmessagetext)
     * @param inline_message_id Identifier of the inline message.
     * @param text New text of the message.
     * @param reply_markup Inline keyboard object.
     * @param parse_mode Send an enum of type ParseMode.
     * @param disable_web_page_preview Disables link previews for links in this
     * message.
     * @return True on success, false otherwise.
     */
    bool editMessageText( const std::string &inline_message_id,
                          const std::string &text,
                          const std::string &reply_markup = "",
                          const EParseMode   parse_mode   = static_cast<EParseMode>( 1 ),
                          const bool         disable_web_page_preview = true );

    /**
     * @brief Edit captions of messages sent by the bot.
     * @details Leaving reply_markup empty remove it from the edited message.
     * (https://core.telegram.org/bots/api#editmessagecaption)
     * @param chat_id Unique identifier for the target chat.
     * @param caption New caption of the message.
     * @param reply_markup Inline keyboard object.
     * @return On success, the edited message.
     */
    std::experimental::optional<const class types::Message>
    editMessageCaption( const int_fast64_t  chat_id,
                        const uint_fast32_t message_id,
                        const std::string & caption      = "",
                        const std::string & reply_markup = "" );

    /**
     * @brief Edit captions of messages sent by the bot.
     * @param chat_id Username of the target channel or group (in the format
     * <code>\@channelusername</code>).
     * (https://core.telegram.org/bots/api#editmessagecaption)
     */
    std::experimental::optional<const class types::Message>
    editMessageCaption( const std::string & chat_id,
                        const uint_fast32_t message_id,
                        const std::string & caption      = "",
                        const std::string & reply_markup = "" );

    /**
     * @brief Edit captions of messages sent by the bot.
     * @details The chat selected will be the chat from where the current update was received.
     * (https://core.telegram.org/bots/api#editmessagecaption)
     */
    std::experimental::optional<const class types::Message>
    editMessageCaption( const uint_fast32_t message_id,
                        const std::string & caption      = "",
                        const std::string & reply_markup = "" );

    /**
     * @brief Edit captions of messages sent via the bot (using inline_queries).
     * @details Leaving reply_markup empty remove it from the edited message.
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
     * @details Leaving reply_markup empty remove it from the edited message.
     * (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @param chat_id Unique identifier for the target chat.
     * @param message_id Unique identifier of the sent message.
     * @param reply_markup New inline keyboard object.
     * @return On success, the edited message.
     */
    std::experimental::optional<const class types::Message>
    editMessageReplyMarkup( const int_fast64_t  chat_id,
                            const uint_fast32_t message_id,
                            const std::string & reply_markup = "" );

    /**
     * @brief Edit only the reply markup of a message sent by the the bot.
     * @param chat_id Username of the target channel or group (in the format
     * <code>\@channelusername</code>).
     * (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @see editMessageReplyMarkup
     */
    std::experimental::optional<const class types::Message>
    editMessageReplyMarkup( const std::string & chat_id,
                            const uint_fast32_t message_id,
                            const std::string & reply_markup = "" );

    /**
     * @brief Edit only the reply markup of a message sent by the the bot.
     * @details The chat selected will be the chat from where the current update was received.
     * (https://core.telegram.org/bots/api#editmessagereplymarkup)
     * @see editMessageReplyMarkup
     */
    std::experimental::optional<const class types::Message>
    editMessageReplyMarkup( const uint_fast32_t message_id, const std::string &reply_markup = "" );

    /**
     * Edit only the reply markup of a message sent via the the bot (using
     * inline queries). Leaving reply_markup empty remove keyboards from the message
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
    std::function<void( T &, const types::Message & )> processMessage = nullptr;

    /**
     * @brief Pointer to the function that will be called on each edited message by the user.
     */
    void ( *processEditedMessage )( T &, const types::Message & ) = nullptr;

    /**
     * @brief Pointer to the function that will be called on each message received in a channel.
     */
    void ( *processChannelPost )( T &, const types::Message & ) = nullptr;

    /**
     * @brief Pointer to the function that will be called on each message modified in a channel.
     */
    void ( *processEditedChannelPost )( T &, const types::Message & ) = nullptr;

    /**
     * @brief Pointer to the function that will be called on each inline query.
     */
    void ( *processInlineQuery )( T &, const types::InlineQuery & ) = nullptr;

    /**
     * @brief Pointer to the function that will be called on each inline query choosed by the user.
     */
    void ( *processChosenInlineResult )( T &, const types::ChosenInlineResult & ) = nullptr;

    /**
     * @brief Pointer to the funciton that will be called on each callback query.
     */
    void ( *processCallbackQuery )( T &, const types::CallbackQuery & ) = nullptr;

    /** @} */

    private:
    /**
     * @internal
     * @brief Forward the update to the functions that will process it.
     * @param Update Update to process.
     */
    void processUpdate( const types::Update &update );

    /** @internal @brief Chat_id of the current user/group/channel. */
    int_fast64_t chat_id;

    /** @internal @brief Id of the current callback query. */
    std::string callback_query_id;

    /** @internal @brief Id of the current inline query. */
    std::string inline_query_id;

    /** @internal @brief Json reader. */
    Json::Reader reader;

    /** @internal @brief Connection to API servers. */
    cpr::Session connection;

    /** @internal @brief Logger object. */
    std::shared_ptr<spdlog::logger> logger_ptr;

    /** @internal @brief Url endpoint for making requests. */
    std::string api_url,

            /** @internal @brief Name of the bot, for logging purposes. */
            bot_name;

    /** @internal @brief Objects that hold all the commands. */
    CommandHandler<T> command_handler;

    /** @internal @brief Inline keyboard handler. */
    Keyboard keyboard_obj;
};
}

#include "basic_bot_impl.hpp"

#endif
