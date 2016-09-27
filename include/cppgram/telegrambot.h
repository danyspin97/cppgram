#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include <string>

/*! \mainpage Reference
 * \authors Stefano Belli, Danilo Spinella
 *
 * \section WhereToGet
 *
 * \subsection GitRepository
 *
 * <a href="https://gitlab.com/WiseDragonStd/cppgram" target="_blank">GitLab - CppGram</a>
 *
 * Cloning repository:
 *
 * $ <tt>git clone https://gitlab.com/WiseDragonStd/cppgram.git</tt>
 *
 * \subsection Branches
 *
 *  - master : main "stable" branch
 *  - dev    : development branch
 *
 * \section DevelopmentInfos
 *
 * \subsection Dependencies
 *
 * This library requires:
 *  - jsoncpp
 *  - cpr
 *  - curl
 *
 * \subsection BuildTools
 *
 *  - CMake
 *  - Make
 *  - GCC / Clang are preferred (tested with GCC 6.2.1)
 *
 * \subsection StaticAnalyzer
 *
 * We <3 CppCheck, analyze using this command:
 *
 * $ <tt>cd src/</tt>
 *
 * $ <tt>cppcheck *.cpp --enable=all --language=c++ --report-progress --verbose -I../include -I/usr/include --force 2>cppgram.log</tt>
 *
 */

namespace Json
{
class Reader;
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
    Json::Reader* reader;
    void processUpdates();
};

}

#include "telegrambot.tpp"

#endif
