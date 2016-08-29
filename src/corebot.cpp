#include "cpr/cpr.h"
#include "json/json.h"
#include "cppgram/corebot.h"
#include "cppgram/exceptions.h"

cppgram::CoreBot::CoreBot(const char* api_token, std::ostream& output)
        : Logger(output), botok(api_token)
{

}

void cppgram::CoreBot::run() const
{
    getUpdates();
}

void cppgram::CoreBot::sendMessage(const char* msg) const
{

}

void cppgram::CoreBot::getUpdates() const
{
    while(1) {
        char fmt[256];
        std::string telegramAPI = "https://api.telegram.org/bot";
        auto response = cpr::Get(cpr::Url{telegramAPI
                                                  .append(botok)
                                                  .append("/getUpdates?timeout=60")});

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

            if (!valroot["ok"].asBool()) {
                log_warn("\"ok\" is not true!");
                throw new NotOkTelegramAPI;
            }

            if (valroot["ok"].asBool() && valroot["result"].empty()) {
                continue;
            }
        }
    }
}

void cppgram::CoreBot::processMessage(const update_msg_t& data) const
{
    //log_event(...);
}

void cppgram::CoreBot::processInlineQuery(const update_cbquery_t& data) const
{
    //log_event(...);
}
