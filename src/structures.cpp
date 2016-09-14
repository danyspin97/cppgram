#include <json/json.h>
#include "cppgram/structures.h"

//TODO

using namespace cppgram;

/* constructors */
chat::chat(Json::Value &val) //ITS DONE!!
{
    id = val["id"].asUInt();
    
    if (!val["type"].isNull()) {
       std::string typechat = val["type"].asString();
       if(typechat == "private")
           type = static_cast<ChatType>(0);
       else if(typechat == "group")
           type = static_cast<ChatType>(1);
       else if(typechat == "supergroup")
           type = static_cast<ChatType>(2);
       else if(typechat == "channel")
           type = static_cast<ChatType>(3);
    }
    
    if (!val["title"].isNull())
        title = val["title"].asString();

    if (!val["username"].isNull())
        username = val["username"].asString();

    if (!val["first_name"])
        first_name = val["first_name"].asString();

    if (!val["last_name"])
        last_name = val["last_name"].asString();
}

message::message(Json::Value &val) //TO FINISH
{
    forward_from = nullptr;
    forward_from_chat = nullptr;
    reply_to_message = nullptr;
    
    message_id = val["message_id"].asUInt();
    from = new struct user(val["from"]);
    date = val["date"].asUInt();
    chat = new struct chat(val["chat"]);

    if (!val["forward_from"].isNull() && val["forward_from"].isObject()) {
        forward_from = new struct user(val["forward_from"]);
        forward_from_chat = new struct chat(val["forward_from_chat"]);
        forward_date = val["forward_date"].asUInt();
    }

    if (!val["reply_to_message"].isNull() && val["reply_to_message"].isObject())
        reply_to_message = new struct message(val["reply_to_message"]);

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

user::user(Json::Value &val) //ITS DONE!
{
    id = val["id"].asUInt();
    first_name = val["first_name"].asString();
    if (!val["last_name"].isNull())
        last_name = val["last_name"].asString();

    if (!val["username"].isNull())
        username = val["username"].asString();
}

inlineQuery::inlineQuery(Json::Value &val) //TO FINISH (just location)
{
    id = val["id"].asUInt();
    from = new struct user(val["from"]);
    if (!val["location"].isNull()) {
        // TODO parseLocation
        //new_inlineQuery.location = parseLocation(val["location"]);
    }
    query = val["query"].asString();
    offset = val["offset"].asUInt();
}

callbackQuery::callbackQuery(Json::Value &val) //SEEMS FINISHED (still to test)
{
    id = val["id"].asUInt();
    from = new struct user(val["from"]);
    message = new struct message(val["message"]);
    inline_message_id = val ["inline_message_id"].asUInt();
    data = val["data"].asString();
}

choosenInlineResult::choosenInlineResult(Json::Value &val) // TO FINISH (just location)
{
    result_id = val["result_id"].asUInt();
    from = new struct user(val["from"]);
    inline_message_id = val["inline_message_id"].asUInt();
    query = val["query"].asString();
}

/* destructors */

//TODO

message::~message()
{
    delete from;
    delete chat;
    
    if(forward_from == NULL) 
        delete forward_from;
    if(forward_from_chat == NULL) 
        delete forward_from_chat;
    if(reply_to_message == NULL) 
        delete reply_to_message;
}

inlineQuery::~inlineQuery()
{
    delete from;
}

callbackQuery::~callbackQuery()
{
    delete from;
    delete message;
}

choosenInlineResult::~choosenInlineResult()
{
    delete from;
}
