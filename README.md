# CppGram
![CppGram build](https://gitlab.com/WiseDragonStd/CppGram/badges/master/build.svg)

Easy C++ wrapper for Telegram Bot API

## Required libraries

 * jsoncpp
 * cpr

 CMake will get these libraries and will configure them (once) for you

 Git is required in order to get the libraries

 libcurl is required in order to use libcpr

## Documentation and guide
 
 Documentation and guide are on the way

## Examples 
 
 Full explained in the docs, you can find examples in the examples/ directory.
 
 EchoBot example is coming with an useful CMakeLists.txt sample for larger projects with CppGram

## How to compile the static library?


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

 * After running CMake, you have to run make in order to compile the library and its dependencies
 ~~~
 $ make
 ~~~

 This will download required dependencies and configure them in order to compile our library.

 * You will find out all the static libraries in ../CppGram/lib

 You can find in the documentation all availible CMake configuration options

## Cleaning 

 * In the build directory to clean (then you need to rebuild the libraries)

 ~~~
 $ make clean
 $ make clean_gitrepo
 ~~~

 * In the source directory to remove useless headers (after building)

 ~~~
 $ ./clean-extra-headers.sh
 ~~~

## How do I link to my own bot?

 *assuming you are using g++ or clang++*

 ~~~
 $ g++ mysrc.cpp -o mybot libcpr.a libjsoncpp.a libcppgram.a -lcurl
 ~~~

 ---

 We reccomend to build YOUR bot on YOUR own computer to get better performance, using these flags:

 ~~~
 -O2 -march=native -mtune=native -Wall -std=c++14
 ~~~


