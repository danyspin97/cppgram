#include <json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;
using namespace std;

InlineKeyboard::InlineKeyboard()
        : column(0), row(0)
{

}

InlineKeyboard::InlineKeyboard(CoreBot* Bot)
        : column(0), row(0), Bot(Bot)
{

}

Json::Value& InlineKeyboard::getKeyboard()
{
    return inline_keyboard;
}

void InlineKeyboard::changeRow()
{
    row++;
    column = 0;
}

bool InlineKeyboard::addButton(string& text, string& data, InlineKeyboardButtonType buttonType)
{
    if (text == "" || data == "")
        throw new InlineKeyboardNotValid;

    if (column == 8)
        changeRow();

    inline_keyboard["inline_keyboard"][row][column]["text"] = text;

    if (buttonType == InlineKeyboardButtonType::CallbackData)
        inline_keyboard["inline_keyboard"][row][column]["callback_data"] = data;
    else if (buttonType == InlineKeyboardButtonType::URL)
        inline_keyboard["inline_keyboard"][row][column]["url"] = data;
    else
        inline_keyboard["inline_keyboard"][row][column]["switch_inline_query"] = data;

    column++;

    return true;
}
