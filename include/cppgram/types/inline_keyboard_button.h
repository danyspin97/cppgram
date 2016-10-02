#ifndef CPPGRAM_INLINE_KEYBOARD_BUTTON_H
#define CPPGRAM_INLINE_KEYBOARD_BUTTON_H

#include <string>

#include <json/json.h>

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Class for creating Inline keyboard button
 * \details This object represents one button of an inline keyboard, used in InlineKeyboard. (https://core.telegram.org/bots/api#inlinekeyboardbutton) */
struct inlineKeyboardButton
{
    /** @} */

    /** \brief Label text of the button */
    std::string text,

    /** \brief Data of the button (depends on type) */
            data;

    /** \brief Type of the button */
    enum InlineKeyboardButtonType button_type;

    /**
     * \brief Constructor by parameters.
     * @param text Label text of the button
     * @param data Data of the button (depends on the type)
     * @param button_type Type of the button to create
     * @return Returns a new inlineKeyboardButton
     */
    inlineKeyboardButton(const std::string &text,
                         const std::string &data,
                         const InlineKeyboardButtonType &button_type)
            : text(text),
              data(data),
              button_type(button_type)
    {}

    /**
     * \brief Constructor by JSON.
     * @param button JSON-serialized button
     * @return Returns a new inlineKeyboardButton
     */
    inlineKeyboardButton(Json::Value &button) : text(button["text"].asString())
    {

        if (!button["callback_data"].isNull())
        {
            data = button["callback_data"].asString();
            button_type = InlineKeyboardButtonType::CallbackData;
        } else if (!button["url"].isNull())
        {
            data = button["url"].asString();
            button_type = InlineKeyboardButtonType::URL;
        } else if (!button["switch_inline_query"].isNull())
        {
            data = button["switch_inline_query"].asString();
            button_type = InlineKeyboardButtonType::SwitchInlineQuery;
        }

    }

    inlineKeyboardButton()
    {}

    ~inlineKeyboardButton()
    {}
};

}

#endif //CPPGRAM_INLINE_KEYBOARD_BUTTON_H
