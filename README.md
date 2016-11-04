# CppGram
[![Build Status](https://travis-ci.org/DanySpin97/cppgram.svg?branch=master)](https://travis-ci.org/DanySpin97/cppgram)

CppGram is a lighweight framework for Telegram Bot API that provides support for the most important api methods and basic features a user need ensuring speed and stability.

## Usage

~~~c++

~~~

## Features
- Designed to handle many updates at a time
- getUpdates support
- Update type based processing
- Inline keyboard support
- Inline query support
- Highly documented

## Dependencies

* jsoncpp (_included_)
* cpr (downloaded if missing)

## Installation
The primary way to include this library in your project is to use git submodule.

~~~
git submodule add git://github.com/DanySpin97/cppgram.git
git submodule update --init --recursive
~~~

Then add the directory in your cmake configuration:

~~~
add_subdirectory(cppgram)
~~~

CppGram will be compiled, libraries and include needs to be included by the project:

~~~
include_directories(${CPPGRAM_INCLUDE_DIRS})
target_link_libraries( your_target_name ${CPPGRAM_LIBRARIES})
~~~

## How do I link to my own bot?

*assuming you are using g++ or clang++*

~~~
$ g++ mysrc.cpp -o mybot libcpr.a libjsoncpp.a libcppgram.a -lcurl
~~~

## Documentation

Documentation: [here](https://danyspin97.github.io/cppgram)

## Authors
CppGram is developed and mantained by [Danilo Spinella](github.com/DanySpin97).

## [License](https://www.gnu.org/licenses/lgpl-3.0.en.html)
CppGram is released under GNU Lesser General Public License. You may copy, distribute and modify the software provided that modifications are described and licensed for free under LGPL-3. Derivatives works (including modifications) can only be redistributed under LGPL-3, but applications that use the framework don't have to be.
