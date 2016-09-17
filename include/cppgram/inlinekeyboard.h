#ifndef INLINE_KEYBOARD_CPPGRAM_H
#define INLINE_KEYBOARD_CPPGRAM_H

#include <string>

namespace Json
{
class Value;
}

namespace cppgram
{

enum InlineKeyboardButtonType : short;

class InlineKeyboard
{
public:
    InlineKeyboard();

protected:
    bool addButton(std::string& text, std::string& data, InlineKeyboardButtonType buttonType);
    bool addButton(const struct inlineKeyboardButton& newButton);
    bool addButton(const struct inlineKeyboardButton* newButtons[]);

    inline void changeRow();
    inline void clearKeyboard();

    void getKeyboard(std::string& reply_markup, bool clearKeyboard = true);
    Json::Value& getKeyboard();

private:
    Json::Value inline_keyboard;
    short column;
    short row;

};

}

#endif
