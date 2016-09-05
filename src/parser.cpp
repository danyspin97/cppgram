#include "json/json.h"
#include "cppgram/structres.h"

using namespace cppgram;

*(*update[]) Parser::parseUpdates(Json::value &val, unsigned short limit)
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
            updates[i] = parseUpdate(val.get(i, null));
        }
        else
        {
            break;
        }
    }
    return &updates;
}

update* Parser::parseUpdate(Json::value &val)
{
    Update update;
    if (val["update_id"].isNumeric())
    {
        update.update_id = val["update_id"].asLargestUInt();
    }
    if (!val["message"].isNull() && val["message"].isObject())
    {
        update.message = parseMessage(val.get("message", nullptr));
    }
    else if (!val["edited_message"].isNull() && val["edited_mesaage"].isObject())
    {
        update.editedMessage = parseMessage(val.get("edited_message", nullptr));
    }
    else if (!val["inline_query"].isNull() && val["inline_query"].isObject())
    {
        update.inlineQuery = parseInlineQuery(val.get("inline_query", nullptr));
    }
    else if (!val["choosen_inline_result"].isNull() && val["choosen_inline_result"].isObject())
    {
        update.choosenInlineResult = parseChoosenInlineResult(val.get("choosen_inline_result", nullptr));
    }
    else if (!val["callback_query"].isNull() && val["callback_query"].isObject())
    {
        update.callbackQuery = parseCallbackQuery(val.get("callback_query", nullptr));
    }

    return &update;
}

message* Parser::parseMessage(Json::value &val)
{
    message message;
    message.message_id = val["message_id"].asLargestUInt();
    message.from = parseUser(val.get("from", nullptr));
    message.date = val["date"].asLargestUInt();
    message.chat = parseChat(val.get("chat", nullptr));
    if (!val["forward_from"].isNull() && val["forward_from"].isObject())
    {
        message.forward_from = parseUser(val.get("forward_from", nullptr));
        message.forward_from_chat = parseChat(val.get("forward_from_chat", nullptr));
        message.forward_date = val["forward_date"].asLargestUInt();
    }
    if (!val["reply_to_message"].isNull() && val["reply_to_message"].isObject())
    {
        message.reply_to_message = parseMessage(val.get("reply_to_message", nullptr));
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
        message.entities = parseMessageEntities(val.get("entites", nullptr));
    }
    else
    {
        message.entities = nullptr;
    }

    return &message;
}

user* Parser::parseUser(Json::value &value)
{
    user user;
    user.id = val["id"].asLargestUInt();
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

chat* Parser::parseChat(Json::value &value)
{
    chat chat;
    chat.id = val["id"].asLargestUInt64();
    chat.type = static_cast<CHAT_TYPE>(val["id"].asCString());
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

*(*messageEntity[]) Parser::parseMessageEntities(Json::value &val)
{
    messageEntity *messageEntity[];
    return &MessageEntity;
}
