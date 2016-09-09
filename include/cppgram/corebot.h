#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "logger.h"
#include "json/forwards.h"

#define TELEGRAMAPI "https://api.telegram.org/bot"


namespace cppgram
{

    enum ParseMode : short;
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
        virtual void processMessage(const struct message& message);
        virtual void processEditedMessage(const struct message& editedMessage);
        virtual void processInlineQuery(const struct inlineQuery& inlineQuery);
        virtual void processChosenInlineResult(const struct choosenInlineResult& choosenInlineResult);
        virtual void processCallbackQuery(const struct callbackQuery& callbackQuery);
        void sendMessage(const char* text,
                         ParseMode pmode = static_cast<ParseMode>(0),
                         bool disable_web_page_preview = true,
                         bool disable_notification = false,
                         uid_32 reply_to_message_id = 0,
                         void* reply_markup = nullptr) const;
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
