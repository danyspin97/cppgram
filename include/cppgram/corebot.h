#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "cppgram/logger.h"

namespace cppgram
{
    //TODO
    typedef union {
        struct msg {
            unsigned long messageId, lastUpdateId, userId, chatId;
            std::string username, date, type, text;
        } message;

        struct cbquery {
            //...
        } callbackQuery;

        //inlineQueries

    } update_t ;

    typedef struct update_t::msg update_msg_t;
    typedef struct update_t::cbquery update_cbquery_t;

    class CoreBot : public Logger
    {
    public:
        CoreBot(const char* api_token,
                std::ostream& output);
        void run() const;
    protected:
        virtual void processMessage(const update_msg_t& data) const;
        virtual void processInlineQuery(const update_cbquery_t& data) const;
        void sendMessage(const char* msg) const;
        //editMessage
    private:
        const std::string botok;
        unsigned long lastUpdateId;
        void getUpdates() const;
    };
}

#endif