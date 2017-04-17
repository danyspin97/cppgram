#ifndef INLINE_KEYBOARD_CPPGRAM_HPP
#define INLINE_KEYBOARD_CPPGRAM_HPP

#include <string>
#include <vector>

#include <json/json.h>

namespace cppgram
{
enum InlineKeyboardButtonType : short;
struct InlineKeyboardButton;

enum InlineKeyboardButtonType : short;

/**
 * \addtogroup Inline Keyboard
 */

/*! \class InlineKeyboard
 * \brief An helper class to create inline keyboard
 * \details Create inline keyboard, get the reply markup with getKeyboard and
 * pass this to api methods.
 * Each method will check for errors (like missing text in button that will
 * result in an API error).
 * The buttons will be added in the same row in sequence; when the (Telegram)
 * limit of 8 buttons in a row is reached, the buttons will be added to the next
 * row.
 * To change row manually call changeRow().
 */
class InlineKeyboard
{
    public:
    /**
     * \brief Default constructor for the function
     * @return An empty object
     */
    InlineKeyboard();

    /**
     * \brief Add a button by passing directly the data
     * @param text Text label
     * @param data Data of the button (depends on the type)
     * @param buttonType Type of the button
     * @return True on success
     */
    bool addButton( const std::string &             text,
                    const std::string &             data,
                    const InlineKeyboardButtonType &button_type );

    /**
     * \brief Add a button by passing a InlineKeyboardButton
     * @param newButton The button to add
     * @return True on success
     */
    bool addButton( const struct InlineKeyboardButton &new_button );

    /**
     * \brief Add button by passing a vector of InlineKeyboardButton
     * @param newButtons
     * @return
     */
    bool addButton( const std::vector<InlineKeyboardButton> &new_buttons );

    /**
     * \brief The button will be added to the next row from now on
     * @return
     */
    unsigned short changeRow();

    /**
     * \brief Clear the inline keyboard of the object
     */
    inline void clearKeyboard() { inline_keyboard.clear(); };
    /**
     * \brief Get keyboard as string
     * \details Pass a string that will be filled with the keyboard
     * @param reply_markup The string that will be filled
     * @param clearKeyboard Clear keyboard after passing it
     */
    void get( std::string &reply_markup, const bool &clear_keyboard = true );

    /**
     * \brief Get keyboard as Json
     * \details This method has to be used in answerInlineQuery, cause it accepts
     * only non JSON-serialized value
     * @return The keyboard as JSON
     */
    //inline Json::Value get() const { return inline_keyboard; };
    private:
    Json::FastWriter writer;
    Json::Value      inline_keyboard;
    unsigned short   column;
    unsigned short   row;
};

/** @} */
}

#endif