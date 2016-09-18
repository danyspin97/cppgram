cmake_minimum_required(VERSION 2.8)
project(cppgram)

find_program(GIT "git")

if(NOT GIT)
	message(FATAL_ERROR "Cannot find git")
endif()

if(NOT NOGET_DEPS)
	set(NOGET_DEPS "no")
	message("Note: You can specify -DNOGET_DEPS=\"yes\" in order to avoid downloading dependencies everytime (if you have installed)")
	if(NOT USE_SYSTEM_CURL)
		set(USE_SYSTEM_CURL ON)
		message("CPR: Using system curl  | USE_SYSTEM_CURL: ${USE_SYSTEM_CURL}")
	endif()

	if(NOT BUILD_CPR_TESTS)
		set(BUILD_CPR_TESTS OFF)
		message("CPR: Not building tests | BUILD_CPR_TESTS: ${BUILD_CPR_TESTS}")
	endif()
endif()

if(NOGET_DEPS STREQUAL "no")
	if(NOT UNIX)
		message(WARN "You must get dependencies your own, put headers in ${CMAKE_SOURCE_DIR}/include and the static lib in  ${CMAKE_SOURCE_DIR}")
	else()
		include(ExternalProject)
		set(DEPENDENCIES_PREFIX "extdep")

		set(CPR_GITHUB_URL "https://github.com/whoshuu/cpr.git")
		set(JSONCPP_GITHUB_URL "https://github.com/open-source-parsers/jsoncpp.git")

		ExternalProject_Add(cpr
			PREFIX ${DEPENDENCIES_PREFIX}
			DOWNLOAD_COMMAND git clone ${CPR_GITHUB_URL}
			CMAKE_ARGS -DUSE_SYSTEM_CURL=${USE_SYSTEM_CURL} -DBUILD_CPR_TESTS=${BUILD_CPR_TESTS}
			INSTALL_COMMAND cp ../cpr/include/cpr/ ${CMAKE_SOURCE_DIR}/include -rv && cp lib/libcpr.a ${CMAKE_SOURCE_DIR}/lib/ -vr
		)

		ExternalProject_Add(jsoncpp
			PREFIX ${DEPENDENCIES_PREFIX}
			DOWNLOAD_COMMAND git clone ${JSONCPP_GITHUB_URL}
			INSTALL_COMMAND cp src/lib_json/libjsoncpp.a ${CMAKE_SOURCE_DIR}/lib/ -vr && cp ../jsoncpp/include/json/ ${CMAKE_SOURCE_DIR}/include -vr
		)

		add_custom_target(clean_gitrepo
			COMMAND rm -rfv {extdep/src/*,extdep/tmp/*})
	endif()
endif()

include_directories(include)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

add_subdirectory(src)
