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
struct inlineKeyboardButton;


enum InlineKeyboardButtonType : short;

/**
 * \addtogroup Inline Keyboard
 */

/*! \class InlineKeyboard
 * \brief This object in an helper class to easy create inline keyboard and pass them as reply markup
 */
class InlineKeyboard
{
public:
    /**
     * \brief Default constructor for the function
     * @return An empty InlineKeyboard object
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

/** @} */

}

#endif
