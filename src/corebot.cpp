#include "cpr/cpr.h"
#include "json/json.h"
#include "cppgram/corebot.h"
#include "cppgram/exceptions.h"
#include "cppgram/osutil.h"

cppgram::CoreBot::CoreBot(const char* api_token, bool background,
                const char* filename,int timeout, int message_limit)
        : Logger(filename), bot_token(api_token), lastUpdateId(0),lastChatId(0),
          timeout(timeout), msg_limit(message_limit)
{
    if(background) {
        int bg=osutil::backgroundProcess();
        if (bg == OSUTIL_NEWPROC_NOTSUPPORTED) {
            log_error("Your operating system is not supported (not yet) for background process");
            throw new BgProcessOSNotSupported;
        } else if(bg == OSUTIL_NEWPROC_FAILED) {
            log_error("Error while creating background process");
            throw new BgProcessFailed;
        } else if(bg == OSUTIL_NEWPROC_SUCCESS)
            log_event("New background process created!!");
    }
}

void cppgram::CoreBot::run()
{
    getUpdates();
}

void cppgram::CoreBot::sendMessage(const char* text,
                                   PARSE_MODE pmode,
                                   bool disable_web_page_preview,
                                   bool disable_notification,
                                   uid_32 reply_to_message_id,
                                   void* reply_markup ) const
{
    char fmt[256];
    std::string parseMode;
    if(pmode == PARSE_MODE::MODE_HTML)
        parseMode="HTML";
    else if(pmode == PARSE_MODE::MODE_MARKDOWN)
        parseMode="Markdown";

    std::string fullURL = std::string(TELEGRAMAPI).append(bot_token)
            .append("/sendMessage?text=")
            .append(text).append("&chat_id=")
            .append(std::to_string(lastChatId))
            .append("&parse_mode=")
            .append(parseMode)
            .append("&disable_notification=")
            .append(std::to_string(disable_notification))
            .append("&disable_web_page_preview=")
            .append(std::to_string(disable_web_page_preview));

    if(reply_to_message_id != 0 && reply_to_message_id > 0)
        fullURL.append("&reply_to_message_id=").append(std::to_string(reply_to_message_id));

    cpr::Response response = cpr::Get(cpr::Url{fullURL});
    if(response.status_code != 200) {
        sprintf(fmt, "(sendMessage) HTTP Response status code is not 200: %d", response.status_code);
        log_warn(fmt);
        throw new NoHTTPOKResponse;
    } else {
        std::string json_doc = response.text;
        Json::Value valroot;
        Json::Reader reader;

        if(!reader.parse(json_doc.c_str(),valroot)) {
            log_error("(sendMessage) Error while parsing JSON document!");
            throw new JsonParseError;
        }

        if(!valroot["ok"].isBool() || valroot["ok"].isNull())
            throwMalformedJson();

        if (!valroot["ok"].asBool()) {
            log_warn("(sendMessage) \"ok\" is not true!");
            throw new NotOkTelegramAPI;
        }
    }
}

void cppgram::CoreBot::parseAssignExecuteUpdate(Json::Value &val)
{
    //TODO FINISH
    uid_32 messageId, from_userId;
    uid_64 chat_chatId;
    std::string text, from_firstName, from_userName;
    std::string chat_firstName, chat_userName, chat_type;
    //struct eventDate //parsedDate
    if (!val["message"].isNull() && val["message"].isObject()) {

        if (!val["message"]["from"].isNull() && val["message"]["from"].isObject()) {
            if (!val["message"]["from"]["id"].isNull() &&
                val["message"]["from"]["id"].isIntegral())
                from_userId = val["message"]["from"]["id"].asLargestUInt();
            else
                throwMalformedJson();

            if (!val["message"]["from"]["first_name"].isNull() &&
                val["message"]["from"]["first_name"].isString())
                from_firstName = val["message"]["from"]["first_name"].asString();
            else
                throwMalformedJson();

            if (!val["message"]["from"]["username"].isNull() &&
                val["message"]["from"]["username"].isString())
                from_userName = val["message"]["from"]["username"].asString();
            else
                throwMalformedJson();
        } else
            throwMalformedJson();

        if (!val["message"]["chat"].isNull() && val["message"]["chat"].isObject()) {
            if (!val["message"]["chat"]["type"].isNull() &&
                val["message"]["chat"]["type"].isString())
                chat_type = val["message"]["chat"]["type"].asString();
            else
                throwMalformedJson();

            if (!val["message"]["chat"]["first_name"].isNull() &&
                val["message"]["chat"]["first_name"].isString())
                chat_firstName = val["message"]["chat"]["first_name"].asString();
            else
                throwMalformedJson();

            if (!val["message"]["chat"]["username"].isNull() &&
                val["message"]["chat"]["username"].isString())
                chat_userName = val["message"]["chat"]["username"].asString();
            else
                throwMalformedJson();

            if (!val["message"]["chat"]["id"].isNull() &&
                val["message"]["chat"]["id"].isIntegral()) {
                chat_chatId = val["message"]["chat"]["id"].asLargestUInt();
                lastChatId = val["message"]["chat"]["id"].asLargestUInt();
            } else
                throwMalformedJson();
        } else
            throwMalformedJson();

        if (!val["message"]["text"].isNull() &&
            val["message"]["text"].isString())
            text = val["message"]["text"].asString();
        else
            throwMalformedJson();

        if (!val["message"]["date"].isNull() &&
            val["message"]["date"].isIntegral())
            std::string unparsedDate = val["message"]["date"].asString();
        else
            throwMalformedJson();

        if (!val["message"]["message_id"].isNull() &&
            val["message"]["message_id"].isIntegral())
            messageId = val["message"]["message_id"].asLargestUInt();
        else
            throwMalformedJson();
    } else
        throwMalformedJson();

    CHAT_TYPE eChat_type;

    if(chat_type == "private")
        eChat_type=CHAT_TYPE::TYPE_PRIVATE;

    struct user* _user = new struct user;
    _user->first_name=from_firstName.c_str();
    _user->user_id=from_userId;
    _user->username=from_userName.c_str();
    _user->last_name=NULL; //to parse

    struct chat* _chat = new struct chat;
    _chat->last_name=NULL; //to parse
    _chat->username=chat_userName.c_str();
    _chat->first_name=chat_firstName.c_str();
    _chat->chat_id=chat_chatId;
    _chat->title=NULL; //to parse
    _chat->type=eChat_type;


    message_t transaction;
    transaction.text=text.c_str();
    transaction.message_id=messageId;
    transaction.chat=_chat;
    transaction.from=_user;
    log_event(std::string("Got Message: ").append(text).append(" ,from: ").append(from_userName).append(" ,chatId: ")
                      .append(std::to_string(chat_chatId)).append(" ,user id: ").append(std::to_string(from_userId))
                      .append(" ,message id: ").append(std::to_string(messageId))
                      .append(" ,chat type: ").append(chat_type)
                      .c_str());
    //call virtual function
    processMessage(transaction);

    //cleanup
    delete _chat;
    delete _user;
}

void cppgram::CoreBot::getUpdates()
{
     while(1) {
        char fmt[256];
         //TODO
         cpr::Response response = cpr::Get(cpr::Url{std::string(TELEGRAMAPI)
                                                  .append(bot_token)
                                                  .append("/getUpdates?timeout=")
                                                  .append(std::to_string(timeout))
                                                  .append("&limit=")
                                                  .append(std::to_string(msg_limit))
                                                  .append("&offset=")
                                                  .append(std::to_string(lastUpdateId+1))
        });

        if(response.status_code != 200) {
            sprintf(fmt, "HTTP Response status code is not 200: %d", response.status_code);
            log_warn(fmt);
            throw new NoHTTPOKResponse;
        } else {
            std::string json_doc = response.text;
            Json::Value valroot;
            Json::Reader doc_reader;
            if (!doc_reader.parse(json_doc, valroot)) {
                log_error("Error while parsing JSON document!");
                throw new JsonParseError;
            }


            if(!valroot["ok"].isBool() || valroot["ok"].isNull())
                throwMalformedJson();

            if(valroot["result"].isNull() || !valroot["result"].isArray())
                throwMalformedJson();

            if (!valroot["ok"].asBool()) {
                log_warn("\"ok\" is not true!");
                throw new NotOkTelegramAPI;
            }

            if (valroot["ok"].asBool() && valroot["result"].empty()) continue;

            for(Json::Value val: valroot["result"]) {
                parseAssignExecuteUpdate(val);

                lastUpdateId = val["update_id"].asLargestUInt();
                log_event(std::string("Last Update ID: ")
                                  .append(std::to_string(lastUpdateId))
                                  .c_str());
            }
        }
    }
}

//virtual functions
void cppgram::CoreBot::processMessage(const message_t &data) const {}
void cppgram::CoreBot::processInlineQuery(const cbquery_t &data) const {}
//

void cppgram::CoreBot::throwMalformedJson() const
{
    log_error("Malformed JSON document!!");
    throw new MalformedJsonDocument;
}
