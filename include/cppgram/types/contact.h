#ifndef CPPGRAM_CONTACT_H
#define CPPGRAM_CONTACT_H
#include <string>

#include <json/json.h>

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** \brief Contact send by a user
 * \details This object represents a phone contact. (https://core.telegram.org/bots/api#contact */
struct contact
{
    /** @} */

    /** \brief Contact's phone number */
    std::string phone_number,

    /** \brief Contact's first name */
            first_name,

    /** \brief <i>Optional</i>. Contact's last name */
            last_name;

    /** \brief <i>Optional</i>. Contact's user identifier in Telegram */
    int_fast32_t user_id;

    contact(Json::Value &jsonContact)
            : phone_number(jsonContact["phone_number"].asString()), first_name(jsonContact["first_name"].asString())
    {
        last_name = !jsonContact["last_name"].isNull() ? jsonContact["last_name"].asString() : "";

        user_id = !jsonContact["user_id"].isNull() ? jsonContact["user_id"].asUInt() : int_fast32_t();
    }

    contact()
    {};

    ~contact()
    {};
};

}

#endif //CPPGRAM_CONTACT_H
