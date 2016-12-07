#ifndef CPPGRAM_ENUMS_H
#define CPPGRAM_ENUMS_H

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Type of the chat */
enum ChatType
        : short
{
    /** Private chats with a user */
            Private = 0,

    /** Group chat (groups with less than 200 members and few admin tools) */
            Group = 1,

    /** Group chat up to 5000 members, shared history, admin tools */
            Supergroup = 2,

    /** Channel */
            Channel = 3
};

/** \brief Type of the entity.
 * \details (https://core.telegram.org/bots/api#messageentity) */
enum MessageEntityType
        : short
{
    /** \@username */
    mention = 0,

    /** #hashatg */
    hashtag = 1,

    /** /start */
    bot_command = 2,

    /** https://telegram.me */
    url = 3,

    /** email\@email.com */
    email = 4,

    /** <b>Bold text</b> */
    bold = 5,

    /** <i>Italic text</i> */
    italic = 6,

    /** <code>Monowidth string</code> */
    code = 7,

    /** <code>Monowidth block</code> */
    pre = 8,

    /** <a href="https://WiseDragonStd.gitlab.io/cppgram" target="_blank">Clickable text URLs</a> */
    text_link = 9,

    /** Mention for user without username */
    text_mention = 10
};

/** \brief Formattation options.
 * \details (https://core.telegram.org/bots/api#formatting-options) */
enum ParseMode
        : short
{
    /** No formattation */
            None = 0,

    /** Formattation using html tags (<b><i>) */
            HTML = 1,

    /** Formattation using markdown (*_) */
            Markdown = 2
};

/** \brief Type of the inlineKeyboardButton to add in the reply markup
 * \details (https://core.telegram.org/bots/api#inlinekeyboardbutton) */
enum InlineKeyboardButtonType
        : short
{
    /** The button will contain a clicable url */
            URL = 0,

    /** The button will contain data that will be sent back to the bot when pressed */
            CallbackData = 1,

    /** Prompt the chat selection, open that chat and insert an inline query. */
            SwitchInlineQuery = 2,

    /** Pressing the button will insert the bot‘s username and the specified inline query in the current chat's input field. Can be empty, in which case only the bot’s username will be inserted */
            SwitchInlineQueryCurrentChat = 3,

    /** Add description of the game that will be launched when the user presses the button */
            CallbackGame = 4
};

/** @} */

enum UpdateType
        : short
{
    Message = 0,
    EditedMessage = 1,
    ChannelPost = 2,
    EditedChannelPost = 3,
    InlineQuery = 4,
    ChoosenInlineResult = 5,
    CallbackQuery = 6
};

}

#endif //CPPGRAM_ENUMS_H
