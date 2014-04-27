/*
 * ASVideoDisplay.h
 *
 *  Created on: 2014-4-22
 *      Author: atomshuai
 */

#ifndef ASVIDEODISPLAY_H_
#define ASVIDEODISPLAY_H_


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

class ASVideoDisplay {
public:
	ASVideoDisplay();
	virtual ~ASVideoDisplay();
	virtual void display(void *data,int height,int width,int size);
	virtual void display(AVFrame* pFrame,AVCodecContext *codecCtx);
	AVFrame* convertColor(AVFrame* pFrame,AVCodecContext *codecCtx);
	void getDestScreen(int *width,int *height);
#ifdef __ANDROID__
	virtual void setDisplayHandle(jobject surface);
#endif

#ifdef __ANDROID__
public:
	jobject surface;
	JNIEnv* env;
	JavaVM *jvm;
	ANativeWindow* window;
#endif
	// RGB data to draw on window
	void * yuvbuffer;
};

#endif /* ASVIDEODISPLAY_H_ */
