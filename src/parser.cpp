#include "json/json.h"
#include "cppgram/structures.h"
#include "cppgram/parser.h"

using namespace cppgram;

void* Parser::parseUpdates(Json::Value &val, unsigned short limit)
{
    update *updates[100];
    if (val.empty())
    {
        return nullptr;
    }
    for (int i = 0; i < limit; i++)
    {
        if (!val[i].isNull() && val[i].isObject())
        {
            updates[i] = parseUpdate(val[i]);
        }
        else
        {
            break;
        }
    }
    return &updates;
}

update* Parser::parseUpdate(Json::Value &val)
{
    update update;
    if (val["update_id"].isNumeric())
    {
        update.update_id = val["update_id"].asUInt();
    }
    if (!val["message"].isNull() && val["message"].isObject())
    {
        update.message = parseMessage(val["message"]);
    }
    else if (!val["edited_message"].isNull() && val["edited_mesaage"].isObject())
    {
        update.editedMessage = parseMessage(val["edited_message"]);
    }
    else if (!val["inline_query"].isNull() && val["inline_query"].isObject())
    {
        update.inlineQuery = parseInlineQuery(val["inline_query"]);
    }
    else if (!val["choosen_inline_result"].isNull() && val["choosen_inline_result"].isObject())
    {
        update.choosenInlineResult = parseChoosenInlineResult(val["choosen_inline_result"]);
    }
    else if (!val["callback_query"].isNull() && val["callback_query"].isObject())
    {
        update.callbackQuery = parseCallbackQuery(val["callback_query"]);
    }

    return &update;
}

message* Parser::parseMessage(Json::Value &val)
{
    message message;
    message.message_id = val["message_id"].asUInt();
    message.from = parseUser(val["from"]);
    message.date = val["date"].asUInt();
    message.chat = parseChat(val["chat"]);
    if (!val["forward_from"].isNull() && val["forward_from"].isObject())
    {
        message.forward_from = parseUser(val["forward_from"]);
        message.forward_from_chat = parseChat(val["forward_from_chat"]);
        message.forward_date = val["forward_date"].asUInt();
    }
    if (!val["reply_to_message"].isNull() && val["reply_to_message"].isObject())
    {
        message.reply_to_message = parseMessage(val["reply_to_message"]);
    }
    if (!val["edit_date"].isNull())
    {
        message.edit_date = val["edit_date"].asLargestUInt();
    }
    else
    {
        message.edit_date = 0;
    }
    if (!val["text"].isNull())
    {
        message.text = val["text"].asCString();
    }
    else
    {
        message.text = nullptr;
    }
    if (!val["entities"].isNull() && val["entities"].isArray())
    {
        //message.entities = parseMessageEntities(val["entites"]);
    }
    else
    {
        message.entities = nullptr;
    }

    return &message;
}

user* Parser::parseUser(Json::Value &val)
{
    user user;
    user.id = val["id"].asUInt();
    user.first_name = val["first_name"].asCString();
    if (!val["last_name"].isNull())
    {
        user.last_name = val["last_name"].asCString();
    }
    else
    {
        user.last_name = nullptr;
    }

    if (!val["username"].isNull())
    {
        user.username = val["username"].asCString();
    }
    else
    {
        user.username = nullptr;
    }
}

chat* Parser::parseChat(Json::Value &val)
{
    chat chat;
    chat.id = val["id"].asUInt64();
    //chat.type = static_cast<CHAT_TYPE>(val["type"].asString());
    if (!val["title"].isNull())
    {
        chat.title = val["title"].asCString();
    }
    else
    {
        chat.title = nullptr;
    }

    if (!val["username"].isNull())
    {
        chat.username = val["username"].asCString();
    }
    else
    {
        chat.username = nullptr;
    }

    if (!val["first_name"])
    {
        chat.first_name = val["first_name"].asCString();
    }
    else
    {
        chat.first_name = nullptr;
    }

    if (!val["last_name"])
    {
        chat.last_name = val["last_name"].asCString();
    }
    else
    {
        chat.last_name = nullptr;
    }

    return &chat;
}
