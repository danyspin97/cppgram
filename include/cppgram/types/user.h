#ifndef CPPGRAM_USER_H
#define CPPGRAM_USER_H

#include <string>
#include <experimental/optional>

#include <json/json.h>

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief User object
 * \details This object represents a Telegram user or bot. [Api reference](https://core.telegram.org/bots/api#user) */
struct user
{
    /** @} */

    /** \brief Unique identifier for this user or bot */
    int_fast32_t id;

    /** \brief User‘s or bot’s first name */
    std::string first_name;

    /** \brief <i>Optional</i>. User‘s or bot’s last name */
    std::experimental::optional<std::string> last_name,

    /** \brief <i>Optional</i>. User‘s or bot’s username */
            username;

    explicit user(Json::Value &jsonUser) : id(jsonUser["id"].asUInt()), first_name(jsonUser["first_name"].asString())
    {

        last_name.emplace(jsonUser["last_name"].asString());

        username.emplace(jsonUser["username"].asString());

    }

    user()
    {}

};

}

#endif //CPPGRAM_USER_H
