# CppGram
![CppGram build](https://gitlab.com/WiseDragonStd/CppGram/badges/master/build.svg)

Easy C++ wrapper for Telegram Bot API

## Required libraries

 * jsoncpp
 * cpr

 CMake will get these libraries and will configure them (once)

 Git is required in order to get the libraries

 libcurl is required in order to use libcpr

## Documentation

 You can find documentation [here](https://gitlab.com/WiseDragonStd/cppgram/wikis/home)
 
 Not finished yet :)

## Examples 
 
 Full explained in the docs, you can find examples in the examples/ directory.
 
 EchoBot example is coming with an useful CMakeLists.txt sample for larger projects with CppGram

## How to compile the static library?
 
 *TWO OPTIONS*:

 Run build.sh
 ~~~
 $ chmod +x build.sh && ./build.sh
 ~~~

 You can run build.sh using these arguments:

 * -fc or --full-clean : will remove the entire build directory after compiling and installing (if requried)
 * -i or --install : will install cppgram headers and static libs (usually /usr/local/lib)
 * -ndg or --nodeps-get : will not get dependencies headers and libraries (cpr and jsoncpp), you need headers for compilation!!

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

  ---

  *Aand... you may want to use your installed cpr and jsoncpp headers / static libraries, without need downloading and building everytime*

  ~~~
  $ cmake ../cppgram-build -DNOGET_DEPS="yes"
  ~~~

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

 ---

 We reccomend to build YOUR bot on YOUR own computer to get better performance, using these flags:

 ~~~
 -O2 -march=native -mtune=native -Wall -std=c++14
 ~~~


