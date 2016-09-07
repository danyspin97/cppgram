#ifndef CPPGRAM_STRUCTURES_H
#define CPPGRAM_STRUCTURES_H


namespace cppgram
{
    typedef unsigned long uid_32;
    typedef unsigned long long uid_64;
    typedef long id_32;
    typedef long long id_64;
    typedef unsigned long date_unix;

    enum CHAT_TYPE
    {
        TYPE_PRIVATE,
        TYPE_GROUP,
        TYPE_SUPERGROUP,
        TYPE_CHANNEL
    };

    enum PARSE_MODE : short
    {
        MODE_HTML,
        MODE_MARKDOWN
    };

    struct chat
    {
        uid_64 id;
        CHAT_TYPE type;
        const char* title, *username,
                *first_name, *last_name;
    };

    struct user
    {
        uid_32 id;
        const char* first_name, *last_name,
        *username;
    };

    struct messageEntity
    {
        //messageEntity_type type;
        int offset;
        int lenght;
        const char* url;
        struct user* user;
    };

    struct text
    {
        const char* full,
                *command,
                *arguments;
    };

    struct message
    {
        uid_32 message_id;
        const struct user* from;
        date_unix date;
        const struct chat* chat;
        const struct user* forward_from;
        const struct chat* forward_from_chat;
        date_unix forward_date;
        const struct message* reply_to_message;
        date_unix edit_date;
        const char* text;
        struct messageEntity (*entities)[];
        struct attachment* message_data;
    };

    enum inline_keyboard_button_type
    {
        url,
        callback_data,
        switch_inline_query
    };

    struct inline_keyboard_button
    {
        const char* text, data;
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
        const struct user* from;
        const struct location* location;
        const char* query;
        uid_32 offset;
    };

    struct choosenInlineResult
    {
        uid_32 result_id;
        const struct user* from;
        const struct location* location;
        uid_32 inline_message_id;
        const char* query;
    };

    struct callbackQuery
    {
        uid_32 id;
        const struct user* from;
        const struct message* message;
        uid_32 inline_message_id;
        const char* data;
    };
}

#endif
