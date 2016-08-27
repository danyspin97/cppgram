CppGram
===

Easy C++ wrapper for Telegram Bot API

Required libraries
===
 
 * jsoncpp
 * cpr 

 CMake will get these libraries and will configure them (once)
 
 Git is required in order to get the libraries

How to compile the static library?
===

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

How do I link to my own bot?
===

 *assuming you are using g++ or clang++*

 ~~~
 $ g++ mysrc.cpp -o mybot libcpr.a libjsoncpp.a libcppgram.a -lcurl
 ~~~

