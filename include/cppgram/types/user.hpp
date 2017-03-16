#ifndef CPPGRAM_USER_HPP
#define CPPGRAM_USER_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

namespace cppgram
{
/** \addtogroup Types
 * @{
 */

/** \brief User object
 * \details This object represents a Telegram user or bot. [Api
 * reference](https://core.telegram.org/bots/api#user) */
class User
{
    /** @} */

    public:
    /** \brief Unique identifier for this user or bot */
    uint_fast32_t id;

    /** \brief User‘s or bot’s first name */
    std::string first_name;

    /** \brief <i>Optional</i>. User‘s or bot’s last name */
    std::experimental::optional<std::string> last_name,

            /** \brief <i>Optional</i>. User‘s or bot’s username */
            username;

    User( Json::Value &json_user )
        : id( json_user["id"].asUInt() )
        , first_name( json_user["first_name"].asString() )
    {
        if ( !json_user["last_name"].isNull() )
        {
            last_name.emplace( json_user["last_name"].asString() );
        }

        if ( !json_user["username"].isNull() )
        {
            username.emplace( json_user["username"].asString() );
        }
    }
};
}

#endif
