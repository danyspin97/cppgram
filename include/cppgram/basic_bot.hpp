#ifndef __CPPGRAM_TELEGRAM_BOT_HPP
#define __CPPGRAM_TELEGRAM_BOT_HPP

#include "cppgram/core_bot.hpp"

/*! \mainpage Reference
 * \section What What is CppGram
 *
 * CppGram is a wrapper for Telegram Messanger Bot API.
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

/*! \namespace cppgram
 *
 * \brief main namespace for CppGram
 *
 */
namespace cppgram
{
/*! \class TelegramBot
 *
 *  \brief contains api methods, update handlers and listener
 *
 */
class BasicBot : public CoreBot
{
    public:
    /*! \fn TelegramBot::TelegramBot(const std::string &api_token,
                const bool &background = false,
                const std::string &filename = "tgbot.log",
                const int_fast32_t &limit = 50,
                const int_fast32_t &timeout = 60)
     * \brief TelegramBot constructor
     * \param api_token: the Bot API token (REQUIRED)
     * \param background: tries to fork the process and put the new in background
     (default: false)
     * \param filename: log output filename/path (default: tgbot.log)
     * \param message_limit: max update limit (default: 50)
     * \param timeout: max timeout for HTTP long polling (default: 100s)
     */
    BasicBot();

    void ( *processMessage )( BasicBot &, const cppgram::message & )         = nullptr;
    void ( *processEditedMessage )( BasicBot &, const cppgram::message & )   = nullptr;
    void ( *processInlineQuery )( BasicBot &, const cppgram::inlineQuery & ) = nullptr;
    void ( *processChosenInlineResult )( BasicBot &, const cppgram::choosenInlineResult & )
        = nullptr;
    void ( *processCallbackQuery )( BasicBot &, const cppgram::callbackQuery & ) = nullptr;

    private:
    void processUpdate();
};
}

#endif
