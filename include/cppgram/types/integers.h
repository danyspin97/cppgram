#ifndef __CPPGRAM_INTEGERS_H
#define __CPPGRAM_INTEGERS_H

namespace cppgram
{

/** \addtogroup Types
 * @{
 */

/** unsigned 32 bit number used as identifier (ex. message_id in message) */
typedef unsigned long uid_32;

/** unsigned 64 bit number used as identifier */
typedef unsigned long long uid_64;

/** Signed 32 bit number */
typedef long id_32;

/** Signed 64 bit number */
typedef long long id_64;

/** Unix date container */
typedef unsigned long date_unix;
/** @} */

}

#endif
