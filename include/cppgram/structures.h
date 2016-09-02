#ifndef CPPGRAM_STRUCTURES_H
#define CPPGRAM_STRUCTURES_H


namespace cppgram
{
    typedef unsigned long uid_32;
    typedef unsigned long long uid_64;
    typedef long id_32;
    typedef long long id_64;
    typedef unsigned long date_unix;
    typedef struct message message_t;
    typedef struct callbackQuery cbquery_t;

    enum CHAT_TYPE
    {
        TYPE_PRIVATE,
        TYPE_GROUP,
        TYPE_SUPERGROUP,
        TYPE_CHANNEL
    };

    struct chat
    {
        uid_64 chat_id;
        CHAT_TYPE type;
        const char* title, *username,
                *first_name, *last_name;
    };

    struct user
    {
        uid_32 user_id;
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

    struct message
    {
        uid_32 message_id;
        struct user* from;
        date_unix date;
        struct chat* chat;
        struct user* forward_from;
        struct chat* forward_from_chat;
        date_unix forward_date;
        struct message* reply_to_message;
        date_unix edit_date;
        const char* text;
        struct messageEntity* (entities[]);
        //struct attachment* message_data;
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

    struct callbackQuery
    {
        //TODO
    };

    //typedef union {
    //    struct message* msg;
    //    struct callbackQuery* cbquery;
    //} update_t;
}

#endif
