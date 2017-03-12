#include "cppgram/basic_bot.hpp"
#include <thread>

namespace cppgram
{
class Polling
{
    public:
    Polling(){};

    Polling( std::vector<cppgram::BasicBot> &bots )
        : bots( bots )
    {
    }

    void run();

    private:
    std::vector<cppgram::BasicBot> bots;
};
}
