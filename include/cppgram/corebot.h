#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "cppgram/logger.h"

struct chat;
struct user;
struct messageEntity;
struct message;

namespace cppgram
{
    class CoreBot : public Logger
    {
    public:
        CoreBot(const char* api_token,
                std::ostream& output);
        void run() const;
        static const char* api_token = "https://api.telegram.org/bot";
    protected:
        virtual void processMessage(const update_msg_t& data) const;
        virtual void processInlineQuery(const update_cbquery_t& data) const;
        void sendMessage(const char* text, void* reply_markup = nullptr, id_32 reply_to_message_id = 0, const char* parse_mode = "HTML", bool disable_web_page_preview = true, bool disable_notification = false) const;
        //editMessage
    private:
        const std::string bot_token;
        unsigned long lastUpdateId;
        void getUpdates() const;
    };
}

#endif
