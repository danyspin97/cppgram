set(COMPILER_WARNINGS "-W -Wall -Wextra") #brutal
set(JSONCPP_STATICLIB "${CMAKE_SOURCE_DIR}/lib/libjsoncpp.a")
set(CPR_STATICLIB "${CMAKE_SOURCE_DIR}/lib/libcpr.a")

include_directories(../include)

file(GLOB_RECURSE SRCS *.cpp)

if(NOT SRCS)
	message(FATAL_ERROR "Cannot find sources! Aborting...")
endif(NOT SRCS)

if(NATIVE STREQUAL "no" OR NOT NATIVE)
	set(NATIVE "")
	message("Note: You can build an optimized executable -DNATIVE=\"yes\"")
elseif(NATIVE STREQUAL "yes")
	set(NATIVE "-march=native -mtune=native")
endif(NATIVE STREQUAL "no" OR NOT NATIVE)

if(NOT ARCH)
	set(ARCH "")
	message("Note: You can specify 64 or 32 bits -DARCH=\"-m32\" -DARCH=\"-m64\"")
endif(NOT ARCH)

if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
	set(CMAKE_CXX_FLAGS "-O2 -std=c++11 ${NATIVE} ${ARCH} ${COMPILER_WARNINGS}")
endif(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")

message("Note: you are building static library, you have to link your executable manually with this and other static libraries (libcppgram.a , libcpr.a , libjsoncpp.a)")
add_library(cppgram 
		STATIC ${SRCS})

install(TARGETS cppgram
	ARCHIVE DESTINATION lib
	LIBRARY DESTINATION lib
	COMPONENT library)

add_dependencies(cppgram jsoncpp cpr)
target_link_libraries(cppgram ${JSONCPP_STATICLIB} ${CPR_STATICLIB})
