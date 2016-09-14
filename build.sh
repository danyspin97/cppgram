#!/bin/sh

CMAKE_ADDITIONAL_FLAGS=""
FULL_CLEAN=false
INSTALL_SYSTEM=false

while [[ $# -gt 0 ]];
do
	k="$1"

	case $k in 
		-ndg | --nodeps-get)
			CMAKE_ADDITIONAL_FLAGS="-DNOGET_DEPS=\"yes\""
			shift
			;;
		-fc | --full-clean)
			FULL_CLEAN=true
			shift
			;;
		-i  | --install)
			INSTALL_SYSTEM=true
			shift
			;;
		*)
			shift
			;;
	esac
done

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
	cmake ${CURRENT_SOURCE_DIR} -DCMAKE_CXX_COMPILER=$(which g++) ${CMAKE_ADDITIONAL_FLAGS} && echo "CMake is done!" || exit 3

	echo "Running make..."
	if make -j${JOBS};
	then
		echo "BUILT LIBRARIES"
		echo "--> Inside lib/ (cd lib) you can find needed libraries! Follow README.md for instructions (Chapter: How do I link to my own bot?)"
	fi

	if $INSTALL_SYSTEM;
	then
		if ! which sudo 2>/dev/null >>/dev/null;
		then
			$(which su) -c "make install" || exit 1
		else
			sudo make install || exit 3
		fi
	fi

	if $FULL_CLEAN;
	then
		cd ${CURRENT_SOURCE_DIR} && rm -rfv ../cppgram-build || exit 4
	fi

	cd ${CURRENT_SOURCE_DIR} || exit 4
fi

