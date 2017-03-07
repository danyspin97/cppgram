#include "CoreBot.hpp"

using std::string;
using std::to_string;

using cppgram::CoreBot;
using cppgram::message;

bool
CoreBot::getUpdates(Json::Value&        updates,
                    const int_fast32_t& offset,
                    const int_fast32_t& limit,
                    const int_fast32_t& timeout)
{

    auto response =
            executeRequest("getUpdates",
                           cpr::Parameters{{"timeout", to_string(timeout)},
                                           {"limit", to_string(limit)},
                                           {"offset", to_string(offset + 1)}});

    if (!checkMethodError(response, updates)) {
        return false;
    }

    if (updates["result"].empty()) {
        return false;
    } else {
        return true;
    }
}

