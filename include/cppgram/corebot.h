#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "cppgram/logger.h"

namespace cppgram
{
    typedef union {
        struct msg {
            long message_id;
            //...
        } message;

        struct cbquery {
            //...
            union chat_id {

            } chatId;
        } callbackQuery;
    } update_t ;

    typedef struct update_t::msg update_msg_t;
    typedef struct update_t::cbquery update_cbquery_t;

    class CoreBot : public Logger
    {
    public:
        CoreBot(const std::string& api_token,
                const std::ofstream& output);
        void runLoop() const;
    protected:
        virtual void processMessage(const update_msg_t& data) const;
        virtual void processInlineQuery(const update_cbquery_t& data) const;
        void sendMessage(const std::string& msg) const;
        //editMessage
    private:
        const std::string botok;
        unsigned long lastUpdateId;
        void getUpdates() const;
    };
}

#endif