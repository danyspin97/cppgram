#include <json/json.h>
#include <mutex>

#include "cppgram/inlinekeyboard.h"
#include "cppgram/exceptions.h"
#include "cppgram/structures.h"
#include "cppgram/singleton.h"

using namespace cppgram;
using namespace std;

std::mutex mtx1;

InlineKeyboard::InlineKeyboard()
        : column(0), row(0)
{}

Json::Value InlineKeyboard::getKeyboard() const
{
    return inline_keyboard;
}

void InlineKeyboard::changeRow()
{
    row++;
    column = 0;
}

bool InlineKeyboard::addButton(const string& text, const string& data, const InlineKeyboardButtonType& buttonType)
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

bool InlineKeyboard::addButton(const struct inlineKeyboardButton &newButton)
{
    return addButton(newButton.text, newButton.data, newButton.button_type);
}

bool InlineKeyboard::addButton(const vector<inlineKeyboardButton>& newButtons)
{
    for (const inlineKeyboardButton& button: newButtons) {
        if (addButton(button.text, button.data, button.button_type) == false)
            return false;
    }
    return true;
}

void InlineKeyboard::clearKeyboard()
{
    inline_keyboard.clear();
}

void InlineKeyboard::getKeyboard(std::string& reply_markup, const bool &clearKeyboard)
{
    mtx1.lock();
    reply_markup = Singleton::getInstance()->getWriter()->write(inline_keyboard);
    mtx1.unlock();

    if (clearKeyboard)
        inline_keyboard.clear();
}
