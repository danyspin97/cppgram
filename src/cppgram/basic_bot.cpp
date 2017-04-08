// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <cpr/cpr.h>
#include <json/json.h>

#include "cppgram/basic_bot.hpp"
#include "cppgram/types/update.hpp"

using std::thread;
using std::vector;
using std::to_string;

using cppgram::BasicBot;
using cppgram::Update;

BasicBot::BasicBot( const BasicBot &b )
    : CoreBot( b )
{
    processMessage       = b.processMessage;
    processEditedMessage = b.processEditedMessage;
    processCallbackQuery = b.processCallbackQuery;
}

void
BasicBot::processUpdate( const Update &update )
{
    switch ( update.type )
    {
        case UpdateType::eMessage:
        {
            chat_id = to_string(update.message->chat.id);
            processMessage( *this, update.message.value() );
            break;
        }
        case UpdateType::eCallbackQuery:
        {
            chat_id           = to_string(update.callback_query->message->chat.id);
            callback_query_id = update.callback_query->id;
            processCallbackQuery( *this, update.callback_query.value() );
            callback_query_id = "";
            break;
        }
        case UpdateType::eEditedMessage:
        {
            chat_id = to_string(update.edited_message->chat.id);
            processEditedMessage( *this, update.edited_message.value() );
            break;
        }
        case UpdateType::eInlineQuery:
        {
            chat_id         = to_string(update.inline_query->from.id);
            inline_query_id = update.inline_query->id;
            processInlineQuery( *this, update.inline_query.value() );
            inline_query_id = "";
            break;
        }
        case UpdateType::eChosenInlineResult:
        {
            chat_id = to_string(update.chosen_inline_result->from.id);
            processChosenInlineResult( *this, update.chosen_inline_result.value() );
            break;
        }
    }
}

void
cppgram::defaultProcessMessage( class BasicBot &bot, const Message & )
{
}
