#include "json/json.h"
#include "cppgram/cppgram.h"

using namespace cppgram;

const message* Parser::parseMessage(Json::Value &val)
{
    message* pmessage = new message;
    message message = *pmessage;
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

    return pmessage;
}

const user* Parser::parseUser(Json::Value &val)
{
    user* puser = new user;
    user user = *puser;
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

    return puser;
}

const chat* Parser::parseChat(Json::Value &val)
{
    chat* pchat = new chat;
    chat chat = *pchat;
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

    return pchat;
}
