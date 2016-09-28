#include <cppgram/cppgram.h>

#define TOKEN "token"

using namespace cppgram;

class MyBot : public TelegramBot
{
    public:
    MyBot() : TelegramBot(TOKEN)
    {}

    // Every time the bot receive a message this function will be called
    void processMessage(const message &message) override final
    {
		  // This is where the button will be stored
		  string gen_button;

        // Create a new keyboard classe to add buttons to a message
        InlineKeyboard keyboard;

        // Add first button that will be clickable and will send "edit" to the bot when pressed
        keyboard.addButton("Edit Me", "edit", InlineKeyboardButtonType::CallbackData);

        //Change row so the next button will be under the last
        keyboard.changeRow();

        // Add the second button as a link to this wrapper source
        keyboard.addButton("Source", "https://gitlab.com/WiseDragonStd/cppgram", InlineKeyboardButtonType::URL);

        // Get the keyboard we created and pass it to sendMessage method
        keyboard.getKeyboard(gen_button);

        // Call the api
        sendMessage(message.chat->id, "Test bot for Cppgram wrapper", gen_button);
    }

    // Every time a user press a bot button of type CallbackQuery this function will be called
    void processCallbackQuery(const callbackQuery &callbackQuery) override final
    {
        // Did the user called a button with callback_data as edit?
        if (callbackQuery.data == "edit") {
            // Is this message been sent by an inline query?
            if (!callbackQuery.inline_message_id.empty()) {
                // Then modify it using inline_message_id
                editMessageText(callbackQuery.inline_message_id, "This is an inline message");
            } else {
                // else modify it by sending the chat id and the message id
                editMessageText(callbackQuery.message->chat->id,
                                callbackQuery.message->id,
                                "This is a message sent by the bot");
            }
            // Then change the message with the data of the button the user pressed
        } else {
            if (!callbackQuery.inline_message_id.empty()) {
                editMessageText(callbackQuery.inline_message_id, callbackQuery.data);
            } else {
                editMessageText(callbackQuery.message->chat->id,
                                callbackQuery.message->id,
                                callbackQuery.data);
            }
        }
    }
};

int main()
{
	 //create the bot with your token (see BotFather)
    MyBot bot;

	 //call run() to start getting updates 
    bot.run(); 

    return 0;
}
