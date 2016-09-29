#ifndef CPPGRAM_STRUCTURES_H
#define CPPGRAM_STRUCTURES_H

#include <string>
#include <vector>

#include "types.h"

//forward Json::Value
namespace Json
{
class Value;
}

namespace cppgram
{

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
    explicit chat(Json::Value &val);
    chat();
};

//identify user
struct user {
    uid_32 id;
    std::string first_name, last_name,
            username;
    explicit user(Json::Value& val);
    user();
};

struct messageEntity {
    // TODO
    //messageEntity_type type;
    int offset,
        lenght;
    std::string url;
    struct user* from;
    
    explicit messageEntity(Json::Value &val);
    ~messageEntity();
    messageEntity(const struct messageEntity& prev);
    messageEntity();
};

//get message data
struct message {
    //TODO
    uid_32 message_id;
    struct user* from;
    date_unix date;
    struct chat* chat;
    struct user* forward_from;
    struct chat* forward_from_chat;
    date_unix forward_date;
    struct message* reply_to_message;
    date_unix edit_date;
    std::string text;
    //struct messageEntity (*entities)[];
    //struct attachment* message_data;
                                                        
    explicit message(Json::Value &val);
    message(const struct message& prev);
    ~message();
    message();
};

struct inlineKeyboardButton {
    std::string text, data;
    enum InlineKeyboardButtonType button_type;
    inlineKeyboardButton(const std::string& text, const std::string& data,
                         const InlineKeyboardButtonType &button_type);
    inlineKeyboardButton(const inlineKeyboardButton& prev);
};

//get location data
struct location {
    float longitude,
          latidute;
};

//get inline query data
struct inlineQuery {
    std::string id, query, offset;
    struct user* from;
    struct location* location;

    explicit inlineQuery(Json::Value& val);
    inlineQuery(const struct inlineQuery& prev);
    ~inlineQuery();
    inlineQuery();
};

//get the choosen result from inline query 
struct choosenInlineResult {
    std::string result_id;
    struct user* from;
    struct location* location;
    uid_32 inline_message_id;
    std::string query;

    explicit choosenInlineResult(Json::Value &val);
    choosenInlineResult(const struct choosenInlineResult& prev);
    ~choosenInlineResult();
    choosenInlineResult();
};

//get callback query data
struct callbackQuery {
    std::string id;
    struct user* from;
    struct message* message;
    std::string inline_message_id;
    std::string data;

    explicit callbackQuery(Json::Value &val);
    callbackQuery(const struct callbackQuery& prev);
    ~callbackQuery();
    callbackQuery();
};

}

#endif
