set(COMPILER_WARNINGS "-W -Wall -Wextra -Wno-unused-parameter -Wno-comment") #brutal

find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)

#fix for Qt Creator not showing cppgram's includes
file(GLOB_RECURSE HEADERS ../include/cppgram/*.hpp)
file(GLOB_RECURSE HEADERS ../include/cppgram/*.h)
file(GLOB_RECURSE TEMPLATES ../include/cppgram/*.tpp)
file(GLOB_RECURSE HEADERS ../include/json/*.h)
add_custom_target(headers SOURCES ${HEADERS})
add_custom_target(templates SOURCES ${TEMPLATES})

if(NOT SOURCES)
    message(FATAL_ERROR "Cannot find sources! Aborting...")
endif(NOT SOURCES)

if(NATIVE STREQUAL "no" OR NOT NATIVE)
    set(NATIVE "")
elseif(NATIVE STREQUAL "yes")
    set(NATIVE "-march=native -mtune=native")
endif(NATIVE STREQUAL "no" OR NOT NATIVE)

if(NOT OPTIMIZATION_LEVEL OR OPTIMIZATION_LEVEL STREQUAL "no")
    set(OPTIMIZATION_LEVEL "")
else()
    set(OPTIMIZATION_LEVEL "-O${OPTIMIZATION_LEVEL}")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    set(CMAKE_CXX_FLAGS "-std=c++14")
    set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZATION_LEVEL} ${NATIVE} ${ARCH} ${COMPILER_WARNINGS}")
    set(CMAKE_CXX_FLAGS_DEBUG "-g ${NATIVE} ${COMPILER_WARNINGS}")
endif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

add_library(cppgram STATIC ${SOURCES})
target_include_directories(cppgram
    PUBLIC ${CPR_INCLUDE_DIRS}
    PUBLIC ${CPPGRAM_INCLUDE_DIRS}
    PUBLIC ${CPPGRAM_INCLUDE_DIRS}/cppgram)
target_link_libraries(cppgram ${CPR_LIBRARIES})

install(TARGETS cppgram
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    COMPONENT library)

add_dependencies(cppgram cpr)

