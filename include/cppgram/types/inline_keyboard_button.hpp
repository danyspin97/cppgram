#ifndef CPPGRAM_InlineKeyboardButton_HPP
#define CPPGRAM_InlineKeyboardButton_HPP

#include <string>

#include <json/json.h>

#include "enums.hpp"

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief Class for creating Inline keyboard json_button
 * \details This object represents one json_button of an inline keyboard, used in InlineKeyboard.
 * (https://core.telegram.org/bots/api#inlinekeyboardbutton) */
class InlineKeyboardButton
{
    /** @} */

    public:
    /** \brief Label text of the json_button */
    std::string text,

            /** \brief Data of the json_button (depends on type) */
            data;

    /** \brief Type of the json_button */
    EButton button_type;

    /**
     * \brief Constructor by parameters.
     * @param text Label text of the json_button
     * @param data Data of the json_button (depends on the type)
     * @param button_type Type of the json_button to create
     * @return Returns a new inlineKeyboardButton
     */
    InlineKeyboardButton( const std::string &text,
                          const std::string &data,
                          const EButton &    button_type )
        : text( text )
        , data( data )
        , button_type( button_type )
    {
    }

    /**
     * \brief Constructor by JSON.
     * @param json_button JSON-serialized button
     * @return Returns a new inlineKeyboardButton
     */
    InlineKeyboardButton( Json::Value &json_button )
        : text( json_button["text"].asString() )
    {
        if ( !json_button["callback_data"].isNull() )
        {
            data        = json_button["callback_data"].asString();
            button_type = EButton::CallbackData;
        }
        else if ( !json_button["url"].isNull() )
        {
            data        = json_button["url"].asString();
            button_type = EButton::URL;
        }
        else if ( !json_button["switch_inline_query"].isNull() )
        {
            data        = json_button["switch_inline_query"].asString();
            button_type = EButton::SwitchInlineQuery;
        }
    }
};
}
}

#endif
