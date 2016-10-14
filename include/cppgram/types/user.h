#ifndef CPPGRAM_USER_H
#define CPPGRAM_USER_H

#include <string>

#include <json/json.h>

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
    int_fast32_t id;

    /** \brief User‘s or bot’s first name */
    std::string first_name,

    /** \brief <i>Optional</i>. User‘s or bot’s last name */
            last_name,

    /** \brief <i>Optional</i>. User‘s or bot’s username */
            username;

    explicit user(Json::Value &jsonUser) : id(jsonUser["id"].asUInt()), first_name(jsonUser["first_name"].asString())
    {

        last_name = !jsonUser["last_name"].isNull() ? jsonUser["last_name"].asString() : "";

        username = !jsonUser["username"].isNull() ? jsonUser["username"] . asString() : "";
    }

    user()
    {}

    ~user()
    {}

};

}

#endif //CPPGRAM_USER_H
