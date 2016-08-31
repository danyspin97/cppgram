#!/bin/sh


if ! which cmake 2>/dev/null >>/dev/null;
then
	echo "CANNOT FIND CMAKE!!!"
	echo "You need CMake in order to build these libraries"
	exit 9
fi

if ! which g++ 2>/dev/null >>/dev/null;
then
	echo "CANNOT FIND G++!!!"
	echo "as we tested this with G++/STD=C++11, you need g++"
	exit 9
fi

if ! which make 2>/dev/null >>/dev/null;
then
	echo "You need make."
	exit 9
fi

if [ -d .git ];
then

	CURRENT_SOURCE_DIR=$(pwd)

	echo "Making build directory"
	mkdir -p ../cppgram-build 2>/dev/null || exit 1 
	
	echo "Changing directory..."
	cd ../cppgram-build 2>/dev/null || exit 2
	
	echo "Running cmake..."
	cmake ${CURRENT_SOURCE_DIR} -DCMAKE_CXX_COMPILER=$(which g++) && echo "CMake is done!" || exit 3

	echo "Running make..."
	if make -j${JOBS};
	then
		echo "BUILT LIBRARIES"
		cd "${CURRENT_SOURCE_DIR}" || exit 4
		echo "--> Inside lib/ (cd lib) you can find needed libraries! Follow README.md for instructions (Chapter: How do I link to my own bot?)"
	fi
fi

