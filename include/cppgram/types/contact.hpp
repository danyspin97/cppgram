#ifndef CPPGRAM_CONTACT_HPP
#define CPPGRAM_CONTACT_HPP

#include <experimental/optional>
#include <string>

#include <json/json.h>

namespace cppgram
{
namespace types
{
/** \addtogroup Types
 * @{
 */

/** \brief Contact send by a user
 * \details This object represents a phone contact. [Api
 * reference](https://core.telegram.org/bots/api#contact */
class Contact
{
    /** @} */

    public:
    /** \brief Contact's phone number */
    std::string phone_number,

            /** \brief Contact's first name */
            first_name;

    /** \brief <i>Optional</i>. Contact's last name */
    std::experimental::optional<std::string> last_name;

    /** \brief <i>Optional</i>. Contact's user identifier in Telegram */
    std::experimental::optional<int_fast32_t> user_id;

    Contact( Json::Value &json_contact )
        : phone_number( json_contact["phone_number"].asString() )
        , first_name( json_contact["first_name"].asString() )
    {
        if ( !json_contact["last_name"].isNull() )
        {
            last_name.emplace( json_contact["last_name"].asString() );
        }

        if ( !json_contact["user_id"].isNull() )
        {
            user_id.emplace( json_contact["user_id"].asUInt() );
        }
    }
};
}
}

#endif
