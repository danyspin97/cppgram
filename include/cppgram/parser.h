#include "json/forwards.h"

namespace cppgram
{

    class Parser
    {
        public:
        static void* parseUpdates(Json::Value &val, unsigned short limit = 100);

        static struct update* parseUpdate(Json::Value &val);

        static struct user* parseUser(Json::Value &val);

        static struct chat* parseChat(Json::Value &val);

        static struct message* parseMessage(Json::Value &val);

        static struct inlineQuery* parseInlineQuery(Json::Value &val);

        static struct choosenInlineResult* parseChoosenInlineResult(Json::Value &val);

        static struct callbackQuery* parseCallbackQuery(Json::Value &val);

        static void* parseMessageEntities();
    };
}
