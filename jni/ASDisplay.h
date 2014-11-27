/*
 * ASDisplay.h
 *
 *  Created on: 2014-5-3
 *      Author: atomshuai
 */

#ifndef ASDISPLAY_H_
#define ASDISPLAY_H_

#include "ASCommon.h"
#include "ASVideoOutput.h"


#ifdef __ANDROID__
#include <jni.h>
#include "ASLog.h"
#include <android/native_window_jni.h>
#endif

//using namespace android;
#ifdef __ANDROID__
extern JNIEnv* JNI_GetEnv();
extern JavaVM* JNI_GetVM();

#endif

extern "C"{
#include<stdio.h>
#include <unistd.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/dict.h>
}


class ASDisplay {
public:
	ASDisplay();
	~ASDisplay();
public:
	virtual int display(unsigned char* data,int width,int height,long size);
#ifdef __ANDROID__
	virtual void setDisplayHandle(jobject surface);
#endif
//public:
//	pVideoState videoState;


#ifdef __ANDROID__
public:
	jobject surface;
	JNIEnv* env;
	JavaVM *jvm;
	ANativeWindow* window;
#endif
	// RGB data to draw on window
	void * yuvbuffer;
	int width_output;
	int heigth_output;
};

#endif /* ASDISPLAY_H_ */
