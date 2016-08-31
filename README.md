# CppGram
![CppGram build](https://gitlab.com/WiseDragonStd/CppGram/badges/master/build.svg)

Easy C++ wrapper for Telegram Bot API

## Required libraries

 * jsoncpp
 * cpr

 CMake will get these libraries and will configure them (once)

 Git is required in order to get the libraries

 libcurl is required in order to use libcpr (RUNTIME!)

## How to compile the static library?
 
 *TWO OPTIONS*:

 Run build.sh
 ~~~
 $ chmod +x build.sh && ./build.sh
 ~~~

 OR

 Do it manually! Enjoy

 * Make a new directory OUTSIDE the source directory
 ~~~
 $ mkdir ../cppgram-build
 ~~~

 * cd to the new directory
 ~~~
 $ cd ../cppgram-build
 ~~~

 * Run CMake to configure the Makefile (you must have CMake 2.8 at least)
 ~~~
 $ cmake ../cppgram-build
 ~~~

  *You may want to use another compiler, then, you have two options:*

  ~~~
  $ CXX=/usr/bin/clang++ cmake ../cppgram-build
  ~~~

  *or*

  ~~~
  $ cmake ../cppgram-build -DCMAKE_CXX_COMPILER=/usr/bin/clang++
  ~~~

  *Clang is just an example!*


 * After running CMake, you have to run make in order to compile the library and its dependencies

 ~~~
 $ make
 ~~~

 This will download required dependencies and configure them in order to compile our library.

 * You will find out all the static libraries in ../CppGram/lib

## Other make rules

 * In the build directory to clean (then you need to rebuild the libraries)

 ~~~
 $ make clean
 $ make clean_gitrepo
 ~~~

 * In the source directory to remove useless headers (after building)

 ~~~
 $ ./clean.sh
 ~~~

## How do I link to my own bot?

 *assuming you are using g++ or clang++*

 ~~~
 $ g++ mysrc.cpp -o mybot libcpr.a libjsoncpp.a libcppgram.a -lcurl
 ~~~

### Examples

 Simple update listener bot

 *mybot.cpp*
 
 ```c++
 #include <cppgram/corebot.h>

 using cppgram::CoreBot;

 class MyBot : public CoreBot
 {
 public:
   MyBot() : CoreBot("apitoken") {}
 };

 int main()
 {
	 MyBot bot;
	 bot.run();

	 return 0;
 }
 ```

 You will find out log in ./tgbot.log, so you can use 

 ~~~
 $ tail -f ./tgbot.log
 ~~~

 to see logs in realtime!


 ---

 Simple update listener bot in background process and custom filename (only with GNU/Linux for now)

 *mybot.cpp*

 ```c++
 #include<cppgram/corebot.h>

 using cppgram::CoreBot;

 class MyBackgroundBot : public CoreBot
 {
 public:
	MyBackgroundBot() : CoreBot("apitoken",true,"/home/user/bot_log.log"){}
 };

 int main()
 {
	 MyBackgroundBot bbot;
	 bbot.run();

	 return 0;
 }
 ```

 More examples on the way :)
  
 ---

 *This is the default cppgram::CoreBot constructor*
 
 *look at this if need to change parameters defaults and/or use them*
 
 ```c++
 public:
        CoreBot(const char* api_token,
                bool background = false,
                const char* filename="tgbot.log",
                int message_limit = 100,
                int timeout = 60
                );
 ```

