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
 * \subsection Cloning repository
 *
 * Clone the repo, build cppgram and then link your own bot:
 *
 *     $ git clone https://gitlab.com/WiseDragonStd/cppgram.git
 *     $ cd cppgram
 *     $ mkdir build
 *     $ cd build
 *     $ cmake ..
 *     $ make
 *
 * This code will download CppGram, its dependency and will build it.
 * Then link you own bot using:
 *
 *     $ g++ main.cpp lib/*.a -lcurl -o bot -Iinclude -std=c++14
 *
 * \subsection Dependencies
 *
 * This library requires:
 *  - jsoncpp
 *  - cpr
 *  - curl
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
 * Put here what your bot answer to messages. Parameter message contains all data about the message received
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
 * \section Compile Compile Options
 *
 * \subsection CMake CMake Configure Options
 *
 * You can configure the project with various options
 *
 *     $ cmake $CPPGRAM_PATH $OPTIONS>
 *
 * Availible options are:
 *
 *      - -DNOGET_DEPS : possible values - "yes" or "no" <tt>-DNOGET:DEPS="yes"</tt> - says that you don't want <tt>make</tt> to download for you any dependency ( default: no)
 *      - -DNATIVE : possible values - "yes" or "no" <tt>-DNATIVE="yes"</tt> - says that you want a natively-built static library for your CPU (default: no) (reccomended) (MAY not work on other CPU)
 *      - -DARCH : possible values - "-m32" or "-m64" <tt>-DARCH="-m64"</tt> - if your compiler has multi-libs, than, if required, you can build lib32/64 libraries (default: nothing, depends on compiler)
 *      - -DOPTIMIZATION_LEVEL : possible values - "2" , "3" , "4", "fast"... - <tt>-DOPTIMIZATION_LEVEL="2"</tt> - says the compiler the optimization level, if desired. (HIGHLY reccomended: 2) (default: nothing)
 *
 *  CMake useful options
 *
 *      - -DCMAKE_CXX_COMPILER : says what compiler you want to use (CppGram is fully working with GCC-C++ {aka g++})
 *      - -DCMAKE_BUILD_TYPE : possible values - "Debug" or "Release" - (default: "Release") <tt>-DCMAKE_BUILD_TYPE="Debug"</tt>
 *
 * A great CMake project configuration command is:
 *
 *      $ cmake ../cppgram -DCMAKE_CXX_COMPILER="/usr/bin/g++" -DNATIVE="yes" -DOPTIMIZATION_LEVEL="2"
 *
 * \subsection MakeRules
 *
 * possible make rules are:
 *
 *  - make : builds the library
 *  - make install : installs headers and static library in PREFIX (choosen by CMake, you can change the prefix using -DCMAKE_INSTALL_PREFIX="/pre/fix" option)
 *  - make gendoc : makes the documentation with doxygen (in ../cppgram/doc)
 *
 * We reccomend to use make with the --jobs=N / -jN option: best value for 'N' is you CPU's cores + 1
 *
 * So, my CPU is Quad-Core, I use --jobs=5 / -j5
 *
 * \section Gurrantee Gurrantee of working wrapper
*
 * This wrapper is TESTED AND WORKS with:
 * 
 *  - Compiler: <tt>GCC-C++ {aka G++} v6.2.1</tt>
 *  - Standard: <tt>C++14</tt>
 *  - CMake version: <tt>v3.6.2</tt>
 *  - Platform: <tt>GNU/Linux (Arch Linux)</tt>
 *  - Doxygen version (docs) : <tt>1.8.12/1.8.x</tt>
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
    std::string bot_token;
    uid_32 updateId;
    const uid_32 timeout, update_limit;
    void processUpdates();
    void parseUpdate(const Json::Value valroot);
};

}

#include "telegrambot.tpp"

#endif
