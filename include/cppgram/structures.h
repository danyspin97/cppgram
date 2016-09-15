/**
 * TODO
 * TO FINISH
 * message
 * messageEntity
 * 
 * here, messages, entities, data types are defined
 * structs constructors / destructors' body are defined in src/structures.cpp
 */
#ifndef CPPGRAM_STRUCTURES_H
#define CPPGRAM_STRUCTURES_H

#include <string>

//forward Json::Value
namespace Json
{
class Value;
}

namespace cppgram
{

//useful and portable data types
typedef unsigned long uid_32;
typedef unsigned long long uid_64;
typedef long id_32;
typedef long long id_64;
typedef unsigned long date_unix;

//message chat type
enum ChatType : short {
    Private = 0,
    Group = 1,
    Supergroup = 2,
    Channel = 3
};

//message markup parser
enum ParseMode : short {
    None = 0,
    HTML = 1,
    Markdown = 2
};

//inline button type
enum InlineKeyboardButtonType : short {
    URL = 0,
    CallbackData = 1,
    SwitchInlineQuery = 2
};

//identify chat
struct chat {
    id_64 id;
    ChatType type;
    std::string title, username,
            first_name, last_name;
    chat(Json::Value &val);
};

//identify user
struct user {
    uid_32 id;
    std::string first_name, last_name,
            username;
    user(Json::Value& val);
};

struct messageEntity {
    // TODO
    //messageEntity_type type;
    int offset,
        lenght;
    std::string url;
    const struct user* user;
};

//get message data
struct message {
    //TODO
    uid_32 message_id;
    const struct user* from;
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
                                                        
    message(Json::Value &val);
    ~message();
};

struct inlineKeyboardButton {
    std::string text, data;
    enum InlineKeyboardButtonType button_type;
};

//get location data
struct location {
    float longitude,
          latidute;
};

//get inline query data
struct inlineQuery {
    std::string id, query, offset;
    const struct user* from;
    const struct location* location;

    inlineQuery(Json::Value &val);
    ~inlineQuery();
};

//get the choosen result from inline query 
struct choosenInlineResult {
    std::string result_id;
    const struct user* from;
    const struct location* location;
    uid_32 inline_message_id;
    std::string query;

    choosenInlineResult(Json::Value &val);
    ~choosenInlineResult();
};

//get callback query data
struct callbackQuery {
    std::string id;
    const struct user* from;
    const struct message* message;
    uid_32 inline_message_id;
    std::string data;

    callbackQuery(Json::Value &val);
    ~callbackQuery();
};

struct inlineKeyboard {

};
    
}

#endif
