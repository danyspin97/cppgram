#ifndef CPPGRAM_EDITBOT_H
#define CPPGRAM_EDITBOT_H

#include <string>
#include "cppgram/types.h"

namespace cppgram
{

enum ParseMode : short;

class EditBot
{
    protected:
    template<typename T>
    uid_32 editMessageText(const T &id,
                       const uid_32 &message_id,
                       const std::string &text,
                       const std::string &reply_markup = "",
                       const ParseMode parse_mode = static_cast<ParseMode>(1),
                       const bool disable_web_page_preview = true) const;

    uid_32 editMessageText(const std::string &inline_message_id,
                       const std::string &text,
                       const std::string &reply_markup = "",
                       const ParseMode parse_mode = static_cast<ParseMode>(1),
                       const bool disable_web_page_preview = true) const;
};

}

#endif //CPPGRAM_EDITBOT_H
