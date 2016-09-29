#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include <string>

/*! \mainpage Reference
 * \section What What is CppGram
 *
 * CppGram is a wrapper for Telegram Messanger Bot API.
 * Designed to be fast and easy, ensures the developer to build a bot in less time without having to learn Telegram Bot API.
 * The bot class (cppgram::TelegramBot) has a method for each API method, so the only thing you have to do is extend this class and start developing you bot!
 *
 * \subsection Features
 *
 * - Getting udpdates using long or short polling (webhook support coming soon)
 * - Support for the most important API methods
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
 * This wrapper has been tested using g++ version 6.2.1. This wrapper haven't been tested with version below.
 *
 * \subsection Cloning Cloning repository
 *
 * This code will download CppGram, its dependency and will build it:
 *
 *     $ git clone https://gitlab.com/WiseDragonStd/cppgram.git
 *     $ cd cppgram
 *     $ mkdir build
 *     $ cd build
 *     $ cmake ..
 *     $ make
 *
 * Then link you own bot using:
 *
 *     $ g++ main.cpp lib/*.a -lcurl -o bot -Iinclude -std=c++14
 *
 * \section How How to use it
 *
 * \subsection processMessage
 *
 * This function will be called everytime your bot receive a message.
 * Override the function adding:
 *
 *     void processMessage(const cppgram::message &message) override;
 *
 * Put here what your bot answer to messages. Parameter message contains all data about the message received.
 *
 * \subsection Inline Keyboards
 *
 * Inline keyboard represent a button below a message.
 * To send a message with a button use this sintax:
 *
 *     // Create the class and add a button
 *     auto keyboard = new InlineKeyboard();
 *     keyboard->addButton("CppGram Documentation", "http://wisedragonstd.gitlab.io/cppgram/", InlineKeyboardButtonType::Url);
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
 * - -DNOGET_DEPS="yes"/"no" (default: "no"): download dependencies (jsoncpp, cpr)
 * - -DNATIVE="yes"/"no" (default: "no", reccomended: "yes"): build a natively-built static library for your CPU (MAY NOT work on all cpu)
 * - -DARCH=/"-m32"/"-m64" (default: not defined): compile the library in a particulary architecture
 * - -DOPTIMIZATION_LEVEL="2"/"3"/"4"/"fast" (default: not defined, reccomended: "2"): set the compiler optmization
 *
 * Sugggested building options
 *      $ cmake ../cppgram -DCMAKE_CXX_COMPILER="/usr/bin/g++" -DNATIVE="yes" -DOPTIMIZATION_LEVEL="2"
 *
 * \section Extra
 *
 * \subsection Authors
 *
 * This wrapper has been developed by <a href="https://gitlab.com/groups/WiseDragonStd" target="_blank">WiseDragonStd</a> (Danilo Spinella, Stefano Belli).
 *
 * \subsection License
 *
 * This software has been released under the <a href="https://gitlab.com/WiseDragonStd/cppgram/blob/master/LICENSE" target="_blank">GNU LGLPv3</a>.
 *
 *
 */

namespace Json
{
class Value;
}

/*! \namespace cppgram
 *
 * \brief main namespace for CppGram
 *
 */
namespace cppgram
{

//forwards
enum ParseMode : short;
typedef unsigned long uid_32;
typedef long long id_64;

/*! \class TelegramBot
 *
 *  \brief contains api methods, update handlers and listener
 *
 */
class TelegramBot
{
public:
    /*! \fn TelegramBot::TelegramBot(const std::string &api_token,
                const bool &background = false,
                const std::string &filename = "tgbot.log",
                const uid_32 &limit = 50,
                const uid_32 &timeout = 60)
     * \brief TelegramBot constructor
     * \param api_token: the Bot API token (REQUIRED)
     * \param background: tries to fork the process and put the new in background (default: false)
     * \param filename: log output filename/path (default: tgbot.log)
     * \param message_limit: max update limit (default: 50)
     * \param timeout: max timeout for HTTP long polling (default: 100s)
     */
    TelegramBot(const std::string &api_token,
                const bool &background = false,
                const std::string &filename = "tgbot.log",
                const uid_32 &limit = 50,
                const uid_32 &timeout = 60);

    /*! \fn void TelegramBot::run()
     * \brief runs infinite loop which handles updates (HTTP long polling "getUpdates" API method)
     */
    void run();

    // Telegram Bot API methods

    template<typename T>
    uid_32 sendMessage(const T &id,
                       const std::string &text,
                       const std::string &reply_markup = "",
                       const ParseMode &parse_mode = static_cast<ParseMode>(1),
                       const bool &disable_web_page_preview = true,
                       const bool &disable_notification = false,
                       const uid_32 &reply_to_message_id = 0) const;

    template<typename T>
    uid_32 editMessageText(const T &id,
                           const uid_32 &message_id,
                           const std::string &text,
                           const std::string &reply_markup = "",
                           const ParseMode &parse_mode = static_cast<ParseMode>(1),
                           const bool &disable_web_page_preview = true) const;

    template<typename T>
    uid_32 editMessageReplyMarkup(const T &id,
                                  const uid_32 &message_id,
                                  const std::string &reply_markup = "") const;

    template<typename T>
    uid_32 editMessageCaption(const T &id,
                              const uid_32 &message_id,
                              const std::string &caption,
                              const std::string &reply_markup = "") const;

    bool editMessageText(const std::string &inline_message_id,
                         const std::string &text,
                         const std::string &reply_markup = "",
                         const ParseMode &parse_mode = static_cast<ParseMode>(1),
                         const bool &disable_web_page_preview = true) const;

    bool editMessageReplyMarkup(const std::string &inline_message_id,
                                const std::string &reply_markup = "") const;

    bool editMessageCaption(const std::string &inline_message_id,
                            const std::string &caption,
                            const std::string &reply_markup = "") const;

    bool answerInlineQuery(const std::string &inline_query_id,
                           const std::string &results,
                           const int &cache_time = 300,
                           const bool &is_personal = false,
                           const std::string &next_offset = "",
                           const std::string &switch_pm_text = "",
                           const std::string &switch_pm_paramter = "") const;
    bool getUpdates(Json::Value &val, const uid_32 &offset = 0,
                    const uid_32 &limit = 100,
                    const uid_32 &timeout = 10);

    // end of Telegram Bot API methods
protected:
    virtual void processMessage(const struct message &message);
    virtual void processEditedMessage(const struct message &editedMessage);
    virtual void processInlineQuery(const struct inlineQuery &inlineQuery);
    virtual void processChosenInlineResult(const struct choosenInlineResult &choosenInlineResult);
    virtual void processCallbackQuery(const struct callbackQuery &callbackQuery);
private:
    const std::string bot_token;
    uid_32 updateId;
    const uid_32 timeout, update_limit;
    void processUpdates();
    void parseUpdate(const Json::Value valroot);
};

}

#include "telegrambot.tpp"

#endif
