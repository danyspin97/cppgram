#ifndef __CPPGRAM_EXCEPTIONS_H
#define __CPPGRAM_EXCEPTIONS_H

#include<exception>

namespace cppgram
{

/*! \class ThreadException
 * \inherits std::exception
 * \brief raises if thread could not start (fatal)
 */
class ThreadException : public std::exception
{
public:
    /*! \fn ThreadException::what() const throw()
     * \return exception message
     */
    virtual const char* what() const throw();
};

/*! \class JsonParseError
 * \inherits std::exception
 * \brief raises if jsoncpp can't parse the JSON document (critical)
 */
class JsonParseError : public std::exception
{
public:
    /*! \fn JsonParseError::what() const throw()
     * \return exception message
     */
    virtual const char* what() const throw();
};

/*! \class BgProcessOSNotSupported
 * \inherits std::exception
 * \brief raises if trying to create new bg process but OS is not supported (fatal)
 */
class BgProcessOSNotSupported : public std::exception
{
public:
    /*! \fn BgProcessOSNotSupported::what() const throw()
     * \return exception message
     */
    virtual const char* what() const throw();
};

/*! \class BgProcessFailed
 * \inherits std::exception
 * \brief raises if the new process failed (fatal)
 */
class BgProcessFailed : public std::exception
{
public:
    /*! \fn BgProcessFailed::what() const throw()
     * \return exception message
     */
    virtual const char* what() const throw();
};

/*! \class InlineKeyboardNotValid
 * \inherits std::exception
 * \brief raises if InlineKeyboard is not valid (critical)
 */
class InlineKeyboardNotValid : public  std::exception
{
public:
    /*! \fn InlineKeyboardNotValid::what() const throw()
     * \return exception message
     */
    virtual const char* what() const throw();
};

}

#endif
