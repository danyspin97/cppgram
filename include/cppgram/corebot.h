#ifndef __CPPGRAM_COREBOT_H
#define __CPPGRAM_COREBOT_H

#include "cppgram/logger.h"

namespace cppgram
{
    class CoreBot : public Logger
    {
    public:
        CoreBot(const std::string& api_token,
                const std::ofstream& output);
        //~CoreBot();
    private:
        const std::string botok;
    };
}

#endif