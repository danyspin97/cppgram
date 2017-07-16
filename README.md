# Cppgram
Cppgram is a lighweight framework for Telegram Bot API that provides support for the most important api methods and basic features a user need, ensuring speed and stability.

## Usage

~~~c++
// Include the framework
#include "cppgram/cppgram.hpp"

using namespace cppgram;

// Create your custom Bot class
class MyBot : public BasicBot<MyBot> {
public:
  MyBot(string &token) : BasicBot(token, "MyBotName", this) {}

  MyBot(const MyBot &b) : BasicBot(b, this) {}
};

// Answer all messages received
void helloWorld(MyBot &bot,
                    const types::Message &message) {

    // sending a "Hello World" message
    bot.sendMessage("Hello World");
}

int main() {
  std::string token = "token";
  auto bot = MyBot(token);
  // Say the bot to answer all messages using our Hello World function
  bot.processMessage = &helloWorld;
  // Create a poll with 8 thread running
  auto poll = Polling<MyBot>(bot, 8);
  poll.run();
}
~~~

## Documentation
You can find Doxygen documentation [here](https://danyspin97.github.io/cppgram).

## Features
- Easy to use
- Receive updates using getUpdates
- Use multithreading to process updates
- A container for each telegram type
- Commands support
- Create inline keyboard
- Create inline query
- Use curl session to avoid re-connecting
- Log warnings and errors
- Highly documented

## Dependencies

* [cpr](https://github.com/whoshuu/cpr)
* [jsoncpp](https://github.com/open-source-parsers/jsoncpp)
* [spdlog](https://github.com/gabime/spdlog)
* [ConcurrentQueue](https://github.com/cameron314/concurrentqueue)

All dependencies are already included and configured.

## Installation
To start using this library you can fork [this repository](https://github.com/DanySpin97/cppgram-example). It is an example project configured with the minimal boilerplate you need to make this library works.

If you already have a project you can include this library using git submodules:

~~~
git submodule add git://github.com/DanySpin97/cppgram.git
git submodule update --init --recursive
~~~

Then add the directory in your cmake configuration:

~~~
add_subdirectory(cppgram)
~~~

Cppgram will be compiled, headers and libraries needs to be included by the project:

~~~
include_directories(${CPPGRAM_INCLUDE_DIRS})
target_link_libraries( your_target_name ${CPPGRAM_LIBRARIES})
~~~

## Authors
Cppgram is developed and mantained by [Danilo Spinella](github.com/DanySpin97).

## [License](https://www.gnu.org/licenses/lgpl-3.0.en.html)
Cppgram is released under GNU Lesser General Public License. You may copy, distribute and modify the software provided that modifications are described and licensed for free under LGPL-3. Derivatives works (including modifications) can only be redistributed under LGPL-3, but applications that use the framework don't have to be.
