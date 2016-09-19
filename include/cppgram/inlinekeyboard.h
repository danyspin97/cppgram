#ifndef INLINE_KEYBOARD_CPPGRAM_H
#define INLINE_KEYBOARD_CPPGRAM_H

#include <string>
#include <vector>

namespace Json
{
class Value;
}

namespace cppgram
{

enum InlineKeyboardButtonType : short;

class InlineKeyboard
{
protected:
    InlineKeyboard();

    bool addButton(const std::string& text, const std::string& data, const InlineKeyboardButtonType& buttonType);
    bool addButton(const struct inlineKeyboardButton& newButton);
    bool addButton(const std::vector<struct inlineKeyboardButton>& newButtons);

    inline void changeRow();
    inline void clearKeyboard();

    void getKeyboard(std::string& reply_markup, const bool &clearKeyboard = true) ;
    Json::Value getKeyboard() const;

private:
    Json::Value inline_keyboard;
    short column;
    short row;

};

}

#endif
