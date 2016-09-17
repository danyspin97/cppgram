#ifndef INLINE_KEYBOARD_CPPGRAM_H
#define INLINE_KEYBOARD_CPPGRAM_H

#include <string>

namespace cppgram
{

enum InlineKeyboardButtonType : short;

class InlineKeyboard
{
    public:
    InlineKeyboard();
    InlineKeyboard(CoreBot* Bot);

    Json::Value& getKeyboard();

    bool addButton(std::string& text, std::string& data, InlineKeyboardButtonType buttonType);

    bool addButton(const struct inlineKeyboardButton& newButton);

    bool addButton(const struct inlineKeyboardButton* newButtons[]);

    inline void changeRow();

    private:
    const CoreBot* Bot;
    Json::Value inline_keyboard;
    short column;
    short row;

};

}

#endif
