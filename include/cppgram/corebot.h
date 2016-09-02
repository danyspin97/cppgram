#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "logger.h"

#define TELEGRAMAPI "https://api.telegram.org/bot"

typedef long id_32;
struct message_t;
struct cbquery_t;

namespace cppgram
{
    class CoreBot : public Logger
    {
    public:
        CoreBot(const char* api_token,
                bool background = false,
                const char* filename="tgbot.log",
                int message_limit = 100,
                int timeout = 60
                );
        void run();
    protected:
        //TODO
        virtual void processMessage(const message_t &data) const;
        virtual void processInlineQuery(const cbquery_t &data) const;
        void sendMessage(const char* text,
                         void* reply_markup = nullptr,
                         id_32 reply_to_message_id = 0,
                         const char* parse_mode = "HTML",
                         bool disable_web_page_preview = true,
                         bool disable_notification = false) const;
        //editMessage
    private:
        const char* bot_token;
        unsigned long lastUpdateId;
        int timeout,msg_limit;
        void getUpdates();
        void throwMalformedJson() const;
    };
}

#endif
