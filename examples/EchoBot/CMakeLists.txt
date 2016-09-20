cmake_minimum_required(VERSION 3.6)
project(EchoBot)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lcurl -g")

include_directories(include)

set ( PROJECT_LINK_LIBS ${CMAKE_SOURCE_DIR}/lib/libcppgram.a ${CMAKE_SOURCE_DIR}/lib/libjsoncpp.a ${CMAKE_SOURCE_DIR}/lib/libcpr.a)
link_directories(${CMAKE_SOURCE_DIR}/lib/)

set(SOURCE_FILES EchoBot.cpp.cpp)
add_executable(EchoBot ${SOURCE_FILES})
target_link_libraries(EchoBot ${PROJECT_LINK_LIBS} )
