#ifndef INLINE_KEYBOARD_CPPGRAM_H
#define INLINE_KEYBOARD_CPPGRAM_H

#include <string>
#include <vector>

namespace Json
{
class Writer;
class Value;
}

namespace cppgram
{

enum InlineKeyboardButtonType : short;

/*! \class InlineKeyboard
 * \brief represents an InlineKeyboard which will be generated later (see getKeyboard() member)
 */
class InlineKeyboard
{
public:
    /*! \fn InlineKeyboard::InlineKeyboard()
     * \brief InlineKeyboard constructor
     */
    InlineKeyboard();

    bool addButton(const std::string& text, const std::string& data, const InlineKeyboardButtonType& buttonType);
    bool addButton(const struct inlineKeyboardButton& newButton);
    bool addButton(const std::vector<struct inlineKeyboardButton>& newButtons);

    void changeRow();
    void clearKeyboard();

    void getKeyboard(std::string& reply_markup, const bool &clearKeyboard = true) ;
    Json::Value getKeyboard() const;

private:
    Json::Writer *writer;
    Json::Value inline_keyboard;
    short column;
    short row;

};

}

#endif
