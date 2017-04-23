#ifndef CPPGRAM_COMMAND_HPP
#define CPPGRAM_COMMAND_HPP

#include <functional>
#include <string>

#include "cppgram/basic_bot.hpp"
#include "cppgram/types/enums.hpp"

namespace cppgram
{
namespace types
{
class Update;
}

namespace commands
{
class Command
{
    public:
    const EUpdate type;

    Command()
        : type( EUpdate::eMessage )
    {
    }

    virtual void callClosure( BasicBot &, const types::Update & ) = 0;
    virtual bool isValid( const types::Update & ) = 0;

    protected:
    void setInlineQueryID(std::string& inline_query_id, BasicBot& bot)
    {
        bot.inline_query_id = inline_query_id;
    }

    void setCallbackQueryID(std::string& callback_query_id, BasicBot& bot)
    {
        bot.callback_query_id = callback_query_id;
    }
};
}
}

#endif
