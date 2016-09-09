#ifndef CPPGRAM_STRUCTURES_H
#define CPPGRAM_STRUCTURES_H
#include <string>

namespace Json
{
class Value;
}

namespace cppgram
{
typedef unsigned long uid_32;
typedef unsigned long long uid_64;
typedef long id_32;
typedef long long id_64;
typedef unsigned long date_unix;

enum ChatType : short
{
    chatPrivate,
    chatGroup,
    chatSupergroup,
    chatChannel
};

enum ParseMode : short
{
    HTML = 0,
    Markdown = 1
};

struct chat
{
    uid_64 id;
    ChatType type;
    std::string title, username,
            first_name, last_name;
    chat(Json::Value &val)
    {
        id = val["id"].asUInt64();
        //chat.type = static_cast<CHAT_TYPE>(val["type"].asString());

        if (!val["title"].isNull())
            title = val["title"].asString();

        if (!val["username"].isNull())
            username = val["username"].asString();

        if (!val["first_name"])
            first_name = val["first_name"].asString();

        if (!val["last_name"])
            last_name = val["last_name"].asString();
    }
};

    struct user
    {
        uid_32 id;
        std::string first_name, last_name,
                username;

        user(Json::Value &val)
        {
            id = val["id"].asUInt();
            first_name = val["first_name"].asString();
            if (!val["last_name"].isNull())
                last_name = val["last_name"].asString();

            if (!val["username"].isNull())
                username = val["username"].asString();
        }
    };

    struct messageEntity
    {
        //messageEntity_type type;
        int offset;
        int lenght;
        std::string url;
        struct user* user;
    };

    struct message
    {
        uid_32 message_id;
        const user* from;
        date_unix date;
        const struct chat* chat;
        const struct user* forward_from;
        const struct chat* forward_from_chat;
        date_unix forward_date;
        const struct message* reply_to_message;
        date_unix edit_date;
        std::string text;
        //struct messageEntity (*entities)[];
        //struct attachment* message_data;

        message(Json::Value &val)
        {
            message_id = val["message_id"].asUInt();
            from = new user(val["from"]);
            date = val["date"].asUInt();
            chat = new struct chat(val["chat"]);

            if (!val["forward_from"].isNull() && val["forward_from"].isObject()) {
                forward_from = new user(val["forward_from"]);
                forward_from_chat = new struct chat(val["forward_from_chat"]);
                forward_date = val["forward_date"].asUInt();
            }

            if (!val["reply_to_message"].isNull() && val["reply_to_message"].isObject())
                reply_to_message = new message(val["reply_to_message"]);

            if (!val["edit_date"].isNull())
                edit_date = val["edit_date"].asUInt();

            if (!val["text"].isNull())
                text = val["text"].asString();

            if (!val["entities"].isNull() && val["entities"].isArray()) {
                //new_message.entities = parseMessageEntities(val["entites"]);
            } else {
                //new_message.entities = nullptr;
            }
        }
    };

    enum inline_keyboard_button_type
    {
        url,
        callback_data,
        switch_inline_query
    };

    struct inline_keyboard_button
    {
        std::string text, data;
        enum inline_keyboard_button_type button_type;
    };

    struct location
    {
        float longitude,
                latidute;
    };

    struct inlineQuery
    {
        uid_32 id;
        const user* from;
        const struct location* location;
        std::string query;
        uid_32 offset;

        inlineQuery(Json::Value &val)
        {
            id = val["id"].asUInt();
            from = new user(val["from"]);
            if (!val["location"].isNull()) {
                // TODO parseLocation
                //new_inlineQuery.location = parseLocation(val["location"]);
            }
            query = val["query"].asString();
            offset = val["offset"].asUInt();
        }
    };

    struct choosenInlineResult
    {
        uid_32 result_id;
        const user* from;
        const struct location* location;
        uid_32 inline_message_id;
        std::string query;

        choosenInlineResult(Json::Value &val)
        {
            result_id = val["result_id"].asUInt();
            from = new user(val["from"]);
            inline_message_id = val["inline_message_id"].asUInt();
            query = val["query"].asString();
        }
    };

    struct callbackQuery
    {
        uid_32 id;
        const struct user* from;
        const struct message* message;
        uid_32 inline_message_id;
        std::string data;

        callbackQuery(Json::Value &val)
        {
            id = val["id"].asUInt();
            from = new user(val["from"]);
            message = new struct message(val["message"]);
            inline_message_id = val ["inline_message_id"].asUInt();
            data = val["data"].asString();
        }
    };
}

#endif
