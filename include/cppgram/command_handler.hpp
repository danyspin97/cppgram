#ifndef CPPGRAM_COMMAND_HANDLER_HPP
#define CPPGRAM_COMMAND_HANDLER_HPP

#include <string>
#include <unordered_map>
#include <vector>

namespace cppgram
{
// Forward declarations
class BasicBot;
enum EUpdate : short;
namespace commands
{
class Command;
}
namespace types
{
class Update;
}

/**
 * @brief Handle bot commands.
 * @details Store commands and check if an update trigger a command.
 */
class CommandHandler
{
    friend class BasicBot;

    public:
    /**
     * @brief Construct this object with empty commands.
     * @param bot Pointer to the bot owner.
     */
    CommandHandler( BasicBot *bot );

    /**
     * @brief Construct this object.
     * @param bot Owner of this object.
     * @param c CommandHandler that owns the commands.
     */
    CommandHandler( BasicBot *bot, const CommandHandler &c );

    /**
     * @internal
     * @brief Copy constructor.
     */
    CommandHandler( const CommandHandler &c );

    /**
     * @internal
     * @brief Assigment operator.
     * @details Assign the exact pwner and all the commands to an other object using the
     * assignation.
     */
    CommandHandler operator=( const CommandHandler &c );

    /**
     * @brief Add a bot command.
     * @param new_command Pointer to the command to add.
     */
    void addCommand( commands::Command *new_command );

    /**
     * @brief copy commands of another object of type `CommandHandler`
     * @param c Objects that owns the command to copy.
     */
    void setCommands( const CommandHandler &c );

    private:
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
    BasicBot *owner;

    /**
     * @internal
     * @brief A map that stores all commands per update type.
     * @details For each update type there is a vector containing pointers to objects of type
     * Command.
     */
    std::unordered_map<const EUpdate, std::vector<commands::Command *>> commands;
};
}

#endif
