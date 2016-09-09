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
    chat(Json::Value &val);
};

struct user
{
    uid_32 id;
    std::string first_name, last_name,
            username;
    user(Json::Value& val);
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
	 ////struct attachment* message_data;

	 message(Json::Value &val);
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

        inlineQuery(Json::Value &val);
    };

    struct choosenInlineResult
    {
        uid_32 result_id;
        const user* from;
        const struct location* location;
        uid_32 inline_message_id;
        std::string query;

        choosenInlineResult(Json::Value &val);
    };

    struct callbackQuery
    {
        uid_32 id;
        const struct user* from;
        const struct message* message;
        uid_32 inline_message_id;
        std::string data;

        callbackQuery(Json::Value &val);
    };
}

#endif
