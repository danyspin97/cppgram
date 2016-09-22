cmake_minimum_required(VERSION 2.8)
project(EchoBot)

include_directories(include)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall")

include(ExternalProject)
set(DEPENDENCIES_PREFIX "extdep")

set(CPPGRAM_GITHUB_URL "https://gitlab.com/WiseDragonStd/cppgram.git")

ExternalProject_Add(cppgram
	PREFIX ${DEPENDENCIES_PREFIX}
	DOWNLOAD_COMMAND git clone ${CPPGRAM_GITHUB_URL}
	INSTALL_COMMAND cp ../cppgram/include/ ${CMAKE_SOURCE_DIR}/include/ -vr && cp ../cppgram/lib/ ${CMAKE_SOURCE_DIR}/ -vr
)

add_custom_target(clean_gitrepo
	COMMAND rm -rfv {extdep/src/*,extdep/tmp/*}
)

set (PROJECT_LINK_LIBS ${CMAKE_SOURCE_DIR}/lib/libcppgram.a ${CMAKE_SOURCE_DIR}/lib/libjsoncpp.a ${CMAKE_SOURCE_DIR}/lib/libcpr.a)
link_directories(${CMAKE_SOURCE_DIR}/lib/)

set(SOURCE_FILES EchoBot.cpp)
add_executable(EchoBot ${SOURCE_FILES})
add_dependencies(EchoBot cppgram)
target_link_libraries(EchoBot ${PROJECT_LINK_LIBS} curl)
