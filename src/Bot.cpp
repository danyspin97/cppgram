#include <cpr/cpr.h>
#include <json/json.h>

#include "Bot.hpp"
#include "types/update.h"
#include "Exceptions.hpp"

using std::thread;
using std::vector;

using cppgram::Bot;

void Bot::processUpdate()
{
    update new_update;

    switch (new_update.type) {
        case UpdateType::Message:
            processMessage(new_update.message.value());
            break;
        case UpdateType::CallbackQuery:
            processCallbackQuery(*new_update.callbackQuery);
            break;
        case UpdateType::EditedMessage:
            processEditedMessage(*new_update.message);
            break;
        case UpdateType::InlineQuery:
            processInlineQuery(*new_update.inlineQuery);
            break;
        case UpdateType::ChoosenInlineResult:
            processChosenInlineResult(*new_update.choosenInlineResult);
            break;
    }
}

// virtual functions
void
Bot::processMessage(const struct message& message)
{
}

void
Bot::processEditedMessage(const struct message& editedMessage)
{
}

void
Bot::processInlineQuery(const struct inlineQuery& inlineQuery)
{
}

void
Bot::processChosenInlineResult(
        const struct choosenInlineResult& choosenInlineResult)
{
}

void
Bot::processCallbackQuery(const struct callbackQuery& callbackQuery)
{
}
