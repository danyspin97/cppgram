#ifndef CPPGRAM_STRUCTURES_H
#define CPPGRAM_STRUCTURES_H

namespace cppgram
{
    typedef long id_32;
    typedef long long id_64;
    typedef unsigned long date_unix;

    enum chat_type
    {
        type_private,
        type_group,
        type_supergroup,
        type_channel
    };

    struct chat
    {
        id_64 chat_id;
        chat_type type;
        char* title,
        username,
        first_name,
        last_name;
    };

    struct user
    {
        id_32 user_id;
        char* first_name,
        last_name,
        username;
    };

    struct messageEntity
    {
        //messageEntity_type type;
        int offset;
        int lenght;
        char* url;
        struct user* user;
    };

    struct message
    {
        id_32 message_id;
        user* from;
        date_unix date;
        struct chat* chat;
        struct user* forward_from;
        struct chat* forward_from_chat;
        date_unix forward_date;
        struct message* reply_to_message;
        date_unix edit_date;
        char* text;
        messageEntity* (entities[]);
        //struct attachment* message_data;
    };

    struct callbackQuery
    {
        //TODO
    };

    typedef union {
        message* msg;
        callbackQuery* cbquery;
    } update_t;
}

#endif