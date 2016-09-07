#include "json/forwards.h"

namespace cppgram
{

    class Parser
    {
        public:
        static const struct user* parseUser(Json::Value &val);

        static const struct chat* parseChat(Json::Value &val);

        static const struct message* parseMessage(Json::Value &val);

        static const struct inlineQuery* parseInlineQuery(Json::Value &val);

        static const struct choosenInlineResult* parseChoosenInlineResult(Json::Value &val);

        static const struct callbackQuery* parseCallbackQuery(Json::Value &val);

        //static void* parseMessageEntities();
    };
}
