// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com

#include "cppgram/exception.hpp"
#include "cppgram/keyboard.hpp"
#include "cppgram/types/enums.hpp"
#include "cppgram/types/keyboard_button.hpp"

using std::string;
using std::vector;

using cppgram::Keyboard;
using cppgram::types::KeyboardButton;
using cppgram::EButton;

Keyboard::Keyboard()
    : column( 0 )
    , row( 0 )
{
    writer.omitEndingLineFeed();
}

unsigned short
Keyboard::changeRow()
{
    column = 0;
    return row++;
}

bool
Keyboard::addButton( const string &text, const string &data, const EButton &button_type )
{
    if ( text.empty() || data.empty() )
    {
        throw KeyboardNotValid();
    }

    if ( column == 8 )
    {
        changeRow();
    }

    inline_keyboard["inline_keyboard"][row][column]["text"] = text;

    if ( button_type == EButton::CallbackData )
    {
        inline_keyboard["inline_keyboard"][row][column]["callback_data"] = data;
    }
    else if ( button_type == EButton::URL )
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
Keyboard::addButton( const struct KeyboardButton &new_button )
{
    return addButton( new_button.text, new_button.data, new_button.button_type );
}

bool
Keyboard::addButton( const vector<KeyboardButton> &new_buttons )
{
    for ( const KeyboardButton &button : new_buttons )
    {
        if ( !addButton( button.text, button.data, button.button_type ) )
        {
            return false;
        }
    }
    return true;
}

void
Keyboard::get( string &reply_markup, const bool &clear_keyboard )
{
    reply_markup = writer.write( inline_keyboard );

    if ( clear_keyboard )
    {
        inline_keyboard.clear();
    }
}
