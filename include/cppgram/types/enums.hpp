#ifndef CPPGRAM_ENUMS_HPP
#define CPPGRAM_ENUMS_HPP

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief Type of the chat */
enum ChatType : short
{
    /** Private chats with a user */
    Private = 0,

    /** Group chat (groups with less than 200 members and few admin tools) */
    Group = 1,

    /** Group chat up to 5000 members, shared history, admin tools */
    Supergroup = 2,

    /** Channel */
    Channel = 3,
};

/** \brief Type of the entity.
 * \details (https://core.telegram.org/bots/api#messageentity) */
enum MessageEntityType : short
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
enum ParseMode : short
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
enum InlineKeyboardButtonType : short
{
    /** The button will contain a clicable url */
    URL = 0,

    /** The button will contain data that will be sent back to the bot when pressed */
    CallbackData = 1,

    /** Prompt the chat selection, open that chat and insert an inline query. */
    SwitchInlineQuery = 2,

    /** Pressing the button will insert the bot‘s username and the specified inline query in the
       current chat's input field. Can be empty, in which case only the bot’s username will be
       inserted */
    SwitchInlineQueryCurrentChat = 3,

    /** Add description of the game that will be launched when the user presses the button */
    CallbackGame = 4
};

/** \brief Service message received. */
enum ServiceMessage : short
{
    /** No service message. */
    none,

    /** The chat photo was deleted. */
    delete_chat_photo,

    /** The group has been created. */
    group_chat_created,

    /** The supergroup has been created. This field can‘t be received in a message coming through
       updates, because bot can’t be a member of a supergroup when it is created. It can only be
       found in reply_to_message if someone replies to a very first message in a directly created
       supergroup. */
    supergroup_chat_created,

    /** The channel has been created. This field can‘t be received in a message coming through
       updates, because bot can’t be a member of a channel when it is created. It can only be found
       in reply_to_message if someone replies to a very first message in a channel. */
    channel_chat_created
};

/** @} */

enum UpdateType : short
{
    eMessage            = 0,
    eEditedMessage      = 1,
    eChannelPost        = 2,
    eEditedChannelPost  = 3,
    eInlineQuery        = 4,
    eChosenInlineResult = 5,
    eCallbackQuery      = 6
};
}

#endif
