#!/usr/bin/bash

function install_dep {
	echo "Attempting to install dependencies from repo"
	apt-get install build-essential cmake git libgtk2.0-dev pkg-config libavcodec-dev libavformat-dev libswscale-dev libjpeg-dev libpng-dev libtiff-dev libjasper-dev
	echo "-> Installed all dependencies"
}

function fetch_opencv {
	echo "Fetching opencv from git"
	git clone https://github.com/Itseez/opencv.git
	echo "-> Fetched opencv from github"
}

function configure_opencv {
	echo "Configuring opencv"
	DIR="$( cd "$( dirname "${BASH_SOURCE[0]}" )" && pwd )"
	cd $DIR/opencv 
	mkdir $DIR/opencv/release
	cd $DIR/opencv/release
	cmake -D CMAKE_BUILD_TYPE=RELEASE -D CMAKE_INSTALL_PREFIX=/usr/local ..
	echo "-> Configured opencv"
}

function compile_opencv {
	echo "Compiling opencv (This may take a LONG time, go get a coffee"
	cd $DIR/opencv/release
	make
	make install
}

function help {
	echo "opencv on 'Buntu install"
	echo "Usage: ./install.sh [Option]"
	echo -e "h \t Display this help"
	echo -e "f \t Full opencv install"
	echo -e "s \t Choose a certain step"
	exit 0
}

# Check for arguments
if [ $# -eq 0 ]
  then
    echo "No arguments supplied"
    help
fi

if [ "$1" == "h" ]; then
	help
elif [ "$1" == "f" ]; then
	install_dep
	fetch_opencv
	configure_opencv
	compile_opencv			
elif [ "$1" == "s" ]; then
	echo "Choose your step"
	echo -e "1) \t Install OpenCV dependencies"
	echo -e "2) \t Fetch OpenCV from git repository"
	echo -e "3) \t Configure OpenCV using cmake"
	echo -e "4) \t Compile and install OpenCV"
	read c
	case $c in 
		1) install_dep;;
		2) fetch_opencv;;
		3) configure_opencv;;
		4) compile_opencv;;
		*) echo "Invalid input";;
	esac	
else 
	echo "No valid argument supplied"
	help
	exit -1
fi
