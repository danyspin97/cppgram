cmake_minimum_required(VERSION 2.8)
project(cppgram)

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
		CMAKE_ARGS -DUSE_SYSTEM_CURL=ON -DBUILD_CPR_TESTS=OFF
		INSTALL_COMMAND cp ../cpr/include/cpr/ ${CMAKE_SOURCE_DIR}/include -rv && cp lib/libcpr.a ${CMAKE_SOURCE_DIR}/lib -v
	)

	ExternalProject_Add(jsoncpp
		PREFIX ${DEPENDENCIES_PREFIX}
		DOWNLOAD_COMMAND git clone ${JSONCPP_GITHUB_URL}
		INSTALL_COMMAND cp src/lib_json/libjsoncpp.a ${CMAKE_SOURCE_DIR}/lib -v && cp ../jsoncpp/include/json/ ${CMAKE_SOURCE_DIR}/include -vr
	)

	add_custom_target(clean_gitrepo
		COMMAND rm -rfv {extdep/src/*,extdep/tmp/*}
		)
endif(NOT UNIX)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/lib")

add_subdirectory(src)
