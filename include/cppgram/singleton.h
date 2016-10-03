#ifndef CPPGRAM_SINGLETON_H
#define CPPGRAM_SINGLETON_H

#include <string>

namespace Json
{
class Reader;
class FastWriter;
class Value;
}

namespace cppgram
{

/*! \class Singleton
 * \brief Singleton class is used inside the project and should not be used with the final bot
 */
class Singleton
{

public:

    /*! \fn Singleton::Singleton(const Singleton &prev) = delete
     * \brief disable copy constructor
     * \param prev: the copied class
     */
    Singleton(const Singleton &prev) = delete;

    /*! \fn Singleton::~Singleton()
     * \brief public Singleton destroyer
     */
    ~Singleton();
    static Singleton *getInstance();
    Json::Reader *getReader() const;
    Json::FastWriter *getWriter() const;
    const std::string &getLogFilename() const;
    void setLogFilename(const std::string &new_filename);

private:
    Singleton();
    static Singleton *instance;
    Json::Reader *reader;
    Json::FastWriter *writer;
    std::string logfilename;
};

}

#endif //CPPGRAM_SINGLETON_H
