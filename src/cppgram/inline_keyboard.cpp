// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include <json/json.h>

#include "cppgram/exception.hpp"
#include "cppgram/inline_keyboard.hpp"
#include "cppgram/types/enums.hpp"
#include "cppgram/types/inline_keyboard_button.hpp"

using std::string;
using std::vector;

using cppgram::InlineKeyboard;
using cppgram::InlineKeyboardButton;
using cppgram::InlineKeyboardButtonType;

InlineKeyboard::InlineKeyboard()
    : column( 0 )
    , row( 0 )
{
}

unsigned short
InlineKeyboard::changeRow()
{
    column = 0;
    return row++;
}

bool
InlineKeyboard::addButton( const string &                  text,
                           const string &                  data,
                           const InlineKeyboardButtonType &button_type )
{
    if ( text.empty() || data.empty() )
    {
        throw InlineKeyboardNotValid();
    }

    if ( column == 8 )
    {
        changeRow();
    }

    inline_keyboard["inline_keyboard"][row][column]["text"] = text;

    if ( button_type == InlineKeyboardButtonType::CallbackData )
    {
        inline_keyboard["inline_keyboard"][row][column]["callback_data"] = data;
    }
    else if ( button_type == InlineKeyboardButtonType::URL )
    {
        inline_keyboard["inline_keyboard"][row][column]["url"] = data;
    }
    else
    {
        inline_keyboard["inline_keyboard"][row][column]["switch_inline_query"] = data;
    }

    column++;

    return true;
}

bool
InlineKeyboard::addButton( const struct InlineKeyboardButton &new_button )
{
    return addButton( new_button.text, new_button.data, new_button.button_type );
}

bool
InlineKeyboard::addButton( const vector<InlineKeyboardButton> &new_buttons )
{
    for ( const InlineKeyboardButton &button : new_buttons )
    {
        if ( !addButton( button.text, button.data, button.button_type ) )
        {
            return false;
        }
    }
    return true;
}

void
InlineKeyboard::getKeyboard( std::string &reply_markup, const bool &clear_keyboard )
{
    Json::FastWriter writer;
    reply_markup = writer.write( inline_keyboard );

    if ( clear_keyboard )
    {
        inline_keyboard.clear();
    }
}
