set(COMPILER_WARNINGS "-W -Wall -Wextra -Wno-unused-parameter") #brutal
set(JSONCPP_STATICLIB libjsoncpp.a)
set(CPR_STATICLIB libcpr.a)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
endif()

#find_package(Threads REQUIRED)

file(GLOB_RECURSE SOURCES *.cpp)

#fix for Qt Creator not showing cppgram's includes
file(GLOB_RECURSE HEADERS ../include/cppgram/*.h)
file(GLOB_RECURSE TEMPLATES ../include/cppgram/*.tpp)
add_custom_target(headers SOURCES ${HEADERS})
add_custom_target(templates SOURCES ${TEMPLATES})

if(NOT SOURCES)
	message(FATAL_ERROR "Cannot find sources! Aborting...")
endif(NOT SOURCES)

if(NATIVE STREQUAL "no" OR NOT NATIVE)
	set(NATIVE "")
	message("Note: You can build an optimized static library -DNATIVE=\"yes\"")
elseif(NATIVE STREQUAL "yes")
	set(NATIVE "-march=native -mtune=native")
endif(NATIVE STREQUAL "no" OR NOT NATIVE)

if(NOT ARCH)
	set(ARCH "")
	message("Note: You can specify 64 or 32 bits -DARCH=\"-m32\" -DARCH=\"-m64\"")
endif(NOT ARCH)

if(NOT OPTIMIZATION_LEVEL OR OPTIMIZATION_LEVEL STREQUAL "no")
    set(OPTIMIZATION_LEVEL "")
    message("Note: You can set an optimization level by using -DOPTIMIZATION_LEVEL=\"INTEGER_LEVEL\" ")
else()
    set(OPTIMIZATION_LEVEL "-O${OPTIMIZATION_LEVEL}")
endif()

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
        set(CMAKE_CXX_FLAGS "-std=c++14")
        set(CMAKE_CXX_FLAGS_RELEASE "${OPTIMIZATION_LEVEL} ${NATIVE} ${ARCH} ${COMPILER_WARNINGS}")
        set(CMAKE_CXX_FLAGS_DEBUG "-g ${NATIVE} ${ARCH} ${COMPILER_WARNINGS}")
endif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

message("Note: you are building static library, you have to link your executable manually with this and other static libraries (libcppgram.a , libcpr.a , libjsoncpp.a)")
add_library(cppgram STATIC ${SOURCES})
#target_link_libraries(cppgram ${CMAKE_LIBS_INIT_THREADS})

install(TARGETS cppgram
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	COMPONENT library)

install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/cppgram
	DESTINATION /usr/include)

if(NOGET_DEPS STREQUAL "no")
	add_dependencies(cppgram cpr jsoncpp)
endif()
