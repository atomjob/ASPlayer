/*
 * ASVideoDisplay.cpp
 *
 *  Created on: 2014-4-22
 *      Author: atomshuai
 */

#include "ASVideoDisplay.h"
#include <string.h>
#ifdef __ANDROID__
#include <jni.h>
#include <android/native_window_jni.h>
#endif


ASVideoDisplay::ASVideoDisplay():
yuvbuffer(0){
#ifdef __ANDROID__
//	env = 	JNI_GetEnv();
	JavaVM* jvm = JNI_GetVM();
	env = NULL;
	bool isDoAttach = false;
	jint ret = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	    /*if( ret == JNI_EDETACHED ) {
	        if( jvm->AttachCurrentThread(&env, NULL) < 0 )
	            return false;
	        isDoAttach = true;
	    }*/

	surface = 0;

	if(isDoAttach)
	{
		jvm->DetachCurrentThread();
	}
#endif
}

ASVideoDisplay::~ASVideoDisplay() {
	av_free(yuvbuffer);
}


void ASVideoDisplay::display(void* data, int height, int width,
		int size) {
#ifdef __ANDROID__
	LOGI("===> ASVideoDisplay::display");
	// JNI ERROR: non-VM thread making JNI call
	if(surface == 0) return;
	ANativeWindow* window = ANativeWindow_fromSurface(env, this->surface);
	ANativeWindow_Buffer buffer;
	if (ANativeWindow_lock(window, &buffer, 0) == 0) {
	  memcpy(buffer.bits, data,  width * height * 2);
	  ANativeWindow_unlockAndPost(window);
	}

	ANativeWindow_release(window);
#endif
}
#ifdef __ANDROID__
void ASVideoDisplay::setDisplayHandle(jobject surface) {
	if(surface != 0){
		this->surface = surface;
	}
}
#endif
AVFrame* ASVideoDisplay::convertColor(AVFrame* pFrame,AVCodecContext *codecCtx) {
	// Allocate an AVFrame structure
//		LOGI("convertColor ==>");
		AVFrame* pFrameRGB = av_frame_alloc();

		// Determine required buffer size and allocate buffer
		int numBytes = avpicture_get_size(AV_PIX_FMT_RGB24,pFrame->width,
				pFrame->height);
		if(yuvbuffer == 0){
			yuvbuffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));
		}


		SwsContext *sws_ctx = sws_getContext(pFrame->width,
				pFrame->height,
				codecCtx->pix_fmt,
				pFrame->width,
				pFrame->height,
				AV_PIX_FMT_RGB24,
				SWS_BILINEAR,
				NULL,NULL,NULL);

		// Assign appropriate parts of buffers to image planes in pFrameRGB
		// Note the pFrameRGB in an AVFrame is a superset of AVPicture
		avpicture_fill((AVPicture*)pFrameRGB,(uint8_t*)yuvbuffer,AV_PIX_FMT_RGB24,
				pFrame->width,pFrame->height);

					// Convert the image from its native format to RGB
		sws_scale(sws_ctx,(uint8_t const * const *)pFrame->data,
					pFrame->linesize,0,
					pFrame->height,
					pFrameRGB->data,
					pFrameRGB->linesize);
		sws_freeContext(sws_ctx);
}

void ASVideoDisplay::display(AVFrame* pFrame,AVCodecContext *codecCtx) {
	static int count = 0;
	AVFrame* pFrameRGB = convertColor(pFrame,codecCtx);
//	static int count = 0;
//	printf("display count = %d width=%d height=%d\n",count,pFrameRGB->width,
//			pFrameRGB->height);
	count++;
//	LOGI("====> count = %d\n",count);
	if(yuvbuffer!=0){
//		LOGI("====> yuvbuffer!=0 =====>\n");
		display(yuvbuffer,pFrame->width,pFrame->height,0);
	}

}
