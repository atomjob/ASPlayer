#!/bin/sh
    export NDK_MODULE_PATH=$NDK_MODULE_PATH:~/Developer/android-ndk-r9/sources/ffmpeg/android
#	ndk-build


	while [ $# != 0 ] 
	do
			case $1 in
				"clean")
					ndk-build clean
					rm -f *.cxx
					rm -f ../src/com/asnetwork/swig/*.java
					exit 0
			esac
			shift
	done

	swig -c++ -java -package com.asnetwork.swig -outdir ../src/com/asnetwork/swig ./swig_build.i
	ndk-build

