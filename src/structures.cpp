#include <json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;

/* constructors */
chat::chat(Json::Value &val) : id(val["id"].asInt64()) //ITS DONE!!
{
    std::string typechat = val["type"].asString();
    if(typechat == "private")
       type = ChatType::Private;
    else if(typechat == "group")
       type = ChatType::Group;
    else if(typechat == "supergroup")
       type = ChatType::Supergroup;
    else if(typechat == "channel")
       type = ChatType::Channel;

    if (!val["title"].isNull())
        title = val["title"].asString();

    if (!val["username"].isNull())
        username = val["username"].asString();

    if (!val["first_name"])
        first_name = val["first_name"].asString();

    if (!val["last_name"])
        last_name = val["last_name"].asString();
}

message::message(Json::Value &val, const std::string& botusern) : message_id(val["message_id"].asUInt()),
                                                                  from(new struct user(val["from"])),
                                                                  date(val["date"].asUInt()),
                                                                  chat(new struct chat(val["chat"])),
																						forward_from(nullptr),
																						forward_from_chat(nullptr),
																						reply_to_message(nullptr)
{
    if (!val["forward_from"].isNull() && val["forward_from"].isObject()) {
        forward_from = new struct user(val["forward_from"]);
        forward_from_chat = new struct chat(val["forward_from_chat"]);
        forward_date = val["forward_date"].asUInt();
    }

    if (!val["reply_to_message"].isNull() && val["reply_to_message"].isObject())
        reply_to_message = new struct message(val["reply_to_message"], botusern);

    if (!val["edit_date"].isNull())
        edit_date = val["edit_date"].asUInt();

    if (!val["text"].isNull()) {
        std::size_t pos;
        text = val["text"].asString();
        if((pos=text.find(botusern)) != std::string::npos) {
            text.replace(pos,botusern.length(),"");
        }
    }

    if (!val["entities"].isNull() && val["entities"].isArray()) {
        //new_message.entities = parseMessageEntities(val["entites"]);
    } else {
        //new_message.entities = nullptr;
    }
}

user::user(Json::Value &val) : id(val["id"].asUInt()), first_name(val["first_name"].asString())
{
    if (!val["last_name"].isNull())
        last_name = val["last_name"].asString();

    if (!val["username"].isNull())
        username = val["username"].asString();
}

inlineQuery::inlineQuery(Json::Value &val) : id(val["id"].asString()),query(val["query"].asString()), 
                                             offset(val["offset"].asString()), from(new struct user(val["from"])),
                                             location(nullptr)
{
    if (!val["location"].isNull()) {
        // TODO parseLocationfulltxt
        //new_inlineQuery.location = parseLocation(val["location"]);
    }
}

callbackQuery::callbackQuery(Json::Value &val, const std::string& botusern) :id(val["id"].asString()),
                                                                             from(new struct user(val["from"])), 
                                                                             message(new struct message(val["message"],botusern)),
                                                                             inline_message_id(val ["inline_message_id"].asUInt()),
                                                                             data(val["data"].asString())

{}

choosenInlineResult::choosenInlineResult(Json::Value &val) : result_id(val["result_id"].asString()), 
                                                             from(new struct user(val["from"])),
                                                             location(nullptr),
                                                             inline_message_id(val["inline_message_id"].asUInt()),
                                                             query(val["query"].asString())
{}

messageEntity::messageEntity(Json::Value& val) : offset(0), lenght(0), url(""), from(nullptr)
{}

/* destructors */

message::~message()
{
    delete from;
    delete chat;
    
    if(forward_from != NULL)
        delete forward_from;
    if(forward_from_chat != NULL)
        delete forward_from_chat;
    if(reply_to_message != NULL)
        delete reply_to_message;
}

inlineQuery::~inlineQuery()
{
    delete from;
    
    if(location != NULL)
        delete location;
}

callbackQuery::~callbackQuery()
{
    delete from;
    delete message;
}

choosenInlineResult::~choosenInlineResult()
{
    delete from;
    
    if(location != NULL)
        delete location;
}

messageEntity::~messageEntity()
{
    if(from != NULL)
        delete from;
}

inlineKeyboardButton::inlineKeyboardButton(const std::string &text,
                                           const std::string &data,
                                           const InlineKeyboardButtonType &button_type)
	: text(text),data(data),button_type(button_type)
{}
