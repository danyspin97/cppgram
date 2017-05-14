#ifndef CPPGRAM_COMMAND_HANDLER_HPP
#define CPPGRAM_COMMAND_HANDLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace cppgram
{
// Forward declarations
template <class T> class BasicBot;
enum EUpdate : short;
namespace commands
{
template <class T> class Command;
}
namespace types
{
class Update;
}

/**
 * @brief Handle bot commands.
 * @details Store commands and check if an update trigger a command.
 */
template <class T> class CommandHandler
{
    template <class Z> friend class BasicBot;

    // static_assert( std::is_base_of<BasicBot<T>, T>::value,
    //"You can only create a command for bot objects." );

    public:
    /**
     * @brief Empty object.
     */
    CommandHandler();

    /**
     * @brief Construct this object with empty commands.
     * @param bot Pointer to the bot owner.
     */
    CommandHandler( T *bot );

    /**
     * @brief Construct this object.
     * @param bot Owner of this object.
     * @param c CommandHandler that owns the commands.
     */
    CommandHandler( T *bot, const CommandHandler &c );

    /**
     * @brief Copy constructor.
     */
    CommandHandler( const CommandHandler &c );

    /**
     * @brief Assigment constructor.
     * @details A CommandHandler will be initialized with the same commands as the rvalue, but the
     * returned object will not have any owner as two CommandHandler objects cannot share the same
     * owner.
     * @param c rvalue.
     * @return CommandHandler object with the same commands as the rvalue.
     */
    CommandHandler &operator=( const CommandHandler &c );

    /**
     * @brief Move assigment operator.
     * @details Assign the exact owner and all the commands to an other object using the
     * assignation.
     * @param c rvalue.
     */
    CommandHandler &operator=( CommandHandler &&c );

    /**
     * @brief Add a bot command.
     * @param new_command Pointer to the command to add.
     */
    void addCommand( commands::Command<T> *new_command );

    /**
     * @brief copy commands of another object of type `CommandHandler`
     * @param c Objects that owns the command to copy.
     */
    void setCommands( const CommandHandler &c );

    private:
    /**
     * @brief Check if this object has an owner and set it to bot if not.
     * @param bot Pointer to the bot owner of this object.
     */
    void init( T *bot );

    /**
     * @internal
     * @brief Check if current update trigger a command.
     * @param update Current update to parse.
     * @return True if the update triggered a command.
     */
    bool processCommands( const types::Update &update );

    /**
     * @internal
     * @brief Bot owner of this object
     */
    T *owner;

    /**
     * @internal
     * @brief A map that stores all commands per update type.
     * @details For each update type there is a vector containing pointers to objects of type
     * Command.
     */
    std::unordered_map<const EUpdate, std::vector<commands::Command<T> *>> commands;
};
}

#include "command_handler_impl.hpp"

#endif
