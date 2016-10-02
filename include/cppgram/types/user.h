#ifndef CPPGRAM_USER_H
#define CPPGRAM_USER_H

#include <string>

#include <json/json.h>

#include "integers.h"

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief User object
 * \details This object represents a Telegram user or bot. (https://core.telegram.org/bots/api#user) */
struct user
{
    /** @} */

    /** \brief Unique identifier for this user or bot */
    uid_32 id;

    /** \brief User‘s or bot’s first name */
    std::string first_name,

    /** \brief <i>Optional</i>. User‘s or bot’s last name */
            last_name,

    /** \brief <i>Optional</i>. User‘s or bot’s username */
            username;

    explicit user(Json::Value &user) : id(user["id"] . asUInt()), first_name(user["first_name"] . asString())
    {

        if (! user["last_name"] . isNull())
            last_name = user["last_name"] . asString();

        if (! user["username"] . isNull())
            username = user["username"] . asString();
    }

    user()
    {}

    ~user()
    {}

};

}

#endif //CPPGRAM_USER_H
