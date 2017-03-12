#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/basic_bot.hpp"
#include "cppgram/types/update.h"

using std::thread;
using std::vector;

using cppgram::Bot;

void
BasicBot::processUpdate( const cppgram::update &update )
{
    switch ( update.type )
    {
    case UpdateType::Message:
        cppgram::message message = update.message.value();
        chat_id                  = message.chat.id;
        processMessage( this, message );
        break;
    case UpdateType::CallbackQuery:
        cppgram::callbackQuery callback_query = update.callback_query.value();
        chat_id                               = callback_query.message.chat.id;
        callback_query_id                     = callback_query.id;
        processCallbackQuery( this, callbackQuery );
        callback_query_id = 0;
        break;
    case UpdateType::EditedMessage:
        edited_message = update.message.value();
        chat_id        = edited_message.chat.id;
        processEditedMessage( this, edited_message );
        break;
    case UpdateType::InlineQuery:
        cppgram::inlineQuery inline_query = update.inline_query.value();

        chat_id         = inline_query.from.id;
        inline_query_id = inline_query.id;
        processInlineQuery( this, inline_query );
        break;
        inline_query_id = 0;
    case UpdateType::ChoosenInlineResult:
        cppgram::choosenInlineResult choosen_inline_result = update.choosen_inline_result.value();

        chat_id = choosen_inline_result.from.id;
        processChosenInlineResult( this, choosenInlineResult );
        break;
    }
}
