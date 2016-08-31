#include "cpr/cpr.h"
#include "json/json.h"
#include "cppgram/corebot.h"
#include "cppgram/exceptions.h"
#include "cppgram/osutil.h"

cppgram::CoreBot::CoreBot(const char* api_token, std::ostream &output,
                          int timeout, int message_limit,bool background)
        : Logger(output), bot_token(api_token), lastUpdateId(0), timeout(timeout), msg_limit(message_limit)
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
                                   void* reply_markup,
                                   id_32 reply_to_message_id,
                                   const char* parse_mode,
                                   bool disable_web_page_preview,
                                   bool disable_notification) const
{

}

void cppgram::CoreBot::getUpdates()
{
     while(1) {
        char fmt[256];
         //TODO
        auto response = cpr::Get(cpr::Url{std::string(TELEGRAMAPI)
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

            if (!valroot["ok"].asBool()) {
                log_warn("\"ok\" is not true!");
                throw new NotOkTelegramAPI;
            }

            if (valroot["ok"].asBool() && valroot["result"].empty()) continue;

            for(Json::Value val: valroot["result"]) {
                log_event("Got updates!");
                //parse json
                lastUpdateId=val["update_id"].asLargestUInt();
                log_event(std::to_string(lastUpdateId).c_str());
            }
        }
    }
}

void cppgram::CoreBot::processMessage(const update_t &data) const
{
    //log_event(...);
}


void cppgram::CoreBot::processInlineQuery(const update_t& data) const
{
    //log_event(...);
}
