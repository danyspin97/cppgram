#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "logger.h"
#include "json/forwards.h"

#define TELEGRAMAPI "https://api.telegram.org/bot"


namespace cppgram
{

    enum PARSE_MODE : short;
    typedef unsigned long uid_32;

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
        void processUpdate(Json::Value &val);
        virtual void processMessage(const struct message* message);
        virtual void processEditedMessage(const struct message* editedMessage);
        virtual void processInlineQuery(const struct inlineQuery* inlineQuery);
        virtual void processChosenInlineResult(const struct choosenInlineResult* choosenInlineResult);
        virtual void processCallbackQuery(const struct callbackQuery* callbackQuery);
        void sendMessage(const char* text,
                         PARSE_MODE pmode,
                         bool disable_web_page_preview,
                         bool disable_notification,
                         uid_32 reply_to_message_id,
                         void* reply_markup) const;
        //editMessage
    private:
        const char* bot_token;
        uid_32 lastUpdateId, lastChatId;
        int timeout, msg_limit;
        void getUpdates();
        void throwMalformedJson() const;
    };
}

#endif
