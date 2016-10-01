#include <json/json.h>
#include <git2/types.h>
#include "cppgram/structures.h"

using namespace cppgram;

/* constructors */
chat::chat(Json::Value &val) : id(val["id"].asInt64()) //ITS DONE!!
{
    std::string typechat = val["type"].asString();
    if (typechat == "private")
        type = ChatType::Private;
    else if (typechat == "group")
        type = ChatType::Group;
    else if (typechat == "supergroup")
        type = ChatType::Supergroup;
    else if (typechat == "channel")
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

message::message(Json::Value &val) : message_id(val["message_id"].asUInt()),
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
        reply_to_message = new struct message(val["reply_to_message"]);

    if (!val["edit_date"].isNull())
        edit_date = val["edit_date"].asUInt();

    if (!val["text"].isNull()) {
        text = val["text"].asString();
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

inlineQuery::inlineQuery(Json::Value &val) : id(val["id"].asString()), query(val["query"].asString()),
                                             offset(val["offset"].asString()), from(new struct user(val["from"])),
                                             location(nullptr)
{
    if (!val["location"].isNull()) {
        // TODO parseLocationfulltxt
        //new_inlineQuery.location = parseLocation(val["location"]);
    }
}

callbackQuery::callbackQuery(Json::Value &val) : id(val["id"].asString()),
                                                 from(new struct user(val["from"])),
                                                 message(new struct message(val["message"])),
                                                 inline_message_id(val["inline_message_id"].asString()),
                                                 data(val["data"].asString())
{}

choosenInlineResult::choosenInlineResult(Json::Value &val) : result_id(val["result_id"].asString()),
                                                             from(new struct user(val["from"])),
                                                             location(nullptr),
                                                             inline_message_id(val["inline_message_id"].asUInt()),
                                                             query(val["query"].asString())
{}

messageEntity::messageEntity(Json::Value &val) : offset(0), lenght(0), url(""), from(nullptr)
{}

inlineKeyboardButton::inlineKeyboardButton(const std::string &text,
                                           const std::string &data,
                                           const InlineKeyboardButtonType &button_type)
        : text(text), data(data), button_type(button_type)
{}

user::user()
{}
message::message()
{}
chat::chat()
{}
messageEntity::messageEntity()
{}
choosenInlineResult::choosenInlineResult()
{}
callbackQuery::callbackQuery()
{}

/* destructors */

message::~message()
{
    delete from;
    delete chat;

    if (forward_from != NULL)
        delete forward_from;
    if (forward_from_chat != NULL)
        delete forward_from_chat;
    if (reply_to_message != NULL)
        delete reply_to_message;
}

inlineQuery::~inlineQuery()
{
    delete from;

    if (location != NULL)
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

    if (location != NULL)
        delete location;
}

messageEntity::~messageEntity()
{
    if (from != NULL)
        delete from;
}

/* copy constructors */
message::message(const message &prev)
{
    chat = new struct chat;
    from = new struct user;
    forward_from = new struct user;
    forward_from_chat = new struct chat;
    reply_to_message = new struct message;

    *chat = *(prev.chat);
    *from = *(prev.from);
    *forward_from = *(prev.forward_from);
    *forward_from_chat = *(prev.forward_from_chat);
    *reply_to_message = *(prev.reply_to_message);

    date = prev.date;
    text = prev.text;
    edit_date = prev.edit_date;
    message_id = prev.message_id;
}

messageEntity::messageEntity(const messageEntity &prev)
{
    from = new struct user;

    *from = *(prev.from);

    url = prev.url;
    offset = prev.offset;
    lenght = prev.lenght;
}

callbackQuery::callbackQuery(const callbackQuery &prev)
{
    from = new struct user;

    *from = *(prev.from);
    *message = *(prev.message);

    id = prev.id;
    inline_message_id = prev.inline_message_id;
    data = prev.data;
}

inlineQuery::inlineQuery(const inlineQuery &prev)
{
    from = new struct user;
    location = new struct location;

    *from = *(prev.from);
    *location = *(prev.location);

    id = prev.id;
    query = prev.query;
    offset = prev.offset;
}

choosenInlineResult::choosenInlineResult(const choosenInlineResult &prev)
{
    from = new struct user;
    location = new struct location;

    *from = *(prev.from);
    *location = *(prev.location);

    result_id = prev.result_id;
    inline_message_id = prev.inline_message_id;
    query = prev.query;
}

update::update()
{}

update::~update()
{}

update::update(Json::Value &update)
{
    if (!update["message"].isNull()) {
        type = UpdateType::Message;
        message = new struct message(update["message"]);
    } else if (!update["callback_query"].isNull()) {
        type = UpdateType::CallbackQuery;
        callbackQuery = new struct callbackQuery(update["callback_query"]);
    } else if (!update["edited_message"].isNull()) {
        type = UpdateType::EditedMessage;
        message = new struct message(update["edited_message"]);
    } else if (!update["inline_query"].isNull()) {
        type = UpdateType::InlineQuery;
        inlineQuery = new struct inlineQuery(update["inline_query"]);
    } else if (!update["choosen_inline_result"].isNull()) {
        type = UpdateType::ChoosenInlineResult;
        choosenInlineResult = new struct choosenInlineResult(update["choosen_inline_result"]);
    }
}
