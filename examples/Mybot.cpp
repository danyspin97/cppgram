#include <iostream>
#include <json/json.h>
#include "cppgram/cppgram.h"

using namespace cppgram;
using namespace std;

class MyBot : public TelegramBot
{
    public:
    MyBot(string token) : TelegramBot(token)
    {}

    // Every time the bot receive a message this function will be called
    void processMessage(const cppgram::message &message) override
    {
        // Create a new keyboard classe to add buttons to a message
        auto keyboard = new InlineKeyboard();
        // Add first button that will be clickable and will send "edit" to the bot when pressed
        keyboard->addButton("Edit Me", "edit", InlineKeyboardButtonType::CallbackData);

        //Change row so the next button will be under the last
        keyboard->changeRow();

        // Add the second button as a link to this wrapper source
        keyboard->addButton("Source", "https://gitlab.com/WiseDragonStd/cppgram", InlineKeyboardButtonType::URL);

        string button_string;
        // Get the keyboard we created and pass it to sendMessage method
        keyboard->getKeyboard(button_string);

        // Call the api
        sendMessage(message.chat->id, "Test bot for Cppgram wrapper", button_string);
    }

    // Every time a user press a bot button of type CallbackQuery this function will be called
    void processCallbackQuery(const cppgram::callbackQuery &callbackQuery) override
    {
        // Did the user called a button with callback_data as edit?
        if (callbackQuery.data == "edit") {
            // Is this message been sent by an inline query?
            if (callbackQuery.inline_message_id != "") {
                // Then modify it using inline_message_id
                editMessageText(callbackQuery.inline_message_id, "This is an inline message");
            } else {
                // else modify it by sending the chat id and the message id
                editMessageText(callbackQuery.message->chat->id,
                                callbackQuery.message->message_id,
                                "This is a message sent by the bot");
            }
            // Then change the message with the data of the button the user pressed
        } else {
            if (callbackQuery.inline_message_id != "") {
                editMessageText(callbackQuery.inline_message_id, callbackQuery.data);
            } else {
                editMessageText(callbackQuery.message->chat->id,
                                callbackQuery.message->message_id,
                                callbackQuery.data);
            }
        }
    }
};

int main()
{
    MyBot bot("token");
    bot.run();

    return 0;
}
