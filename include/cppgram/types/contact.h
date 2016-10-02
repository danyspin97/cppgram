#ifndef CPPGRAM_CONTACT_H
#define CPPGRAM_CONTACT_H
#include <string>

#include <json/json.h>

#include "integers.h"

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
    uid_32 user_id;

    contact(Json::Value &contact)
            : phone_number(contact["phone_number"].asString()), first_name(contact["first_name"].asString())
    {
        if (!contact["last_name"].isNull())
            last_name = contact["last_name"].asString();

        if (!contact["user_id"].isNull())
            user_id = contact["user_id"].asUInt();
    }

    contact()
    {};

    ~contact()
    {};
};

}

#endif //CPPGRAM_CONTACT_H
