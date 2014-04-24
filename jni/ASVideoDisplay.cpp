/*
 * ASVideoDisplay.cpp
 *
 *  Created on: 2014-4-22
 *      Author: atomshuai
 */

#include "ASVideoDisplay.h"
#include <string.h>



ASVideoDisplay::ASVideoDisplay():
yuvbuffer(0){
#ifdef __ANDROID__
	env =  JNI_GetEnv();
	jvm = JNI_GetVM();
	window = 0;
#endif
}

ASVideoDisplay::~ASVideoDisplay() {
	av_free(yuvbuffer);
	if(window!=0){
		ANativeWindow_release(window);
		window = 0;
	}
	if(surface!=0){
		LOGI("===>~ASVideoDisplay");
//		env->DeleteGlobalRef(surface);
		LOGI("~ASVideoDisplay===>");
//		surface = 0;
	}
}


void ASVideoDisplay::display(void* data, int height, int width,
		int size) {
#ifdef __ANDROID__
	LOGI("===> ASVideoDisplay::display");
	//Should AttachCurrentThread if not cause JNI ERROR: non-VM thread making JNI call
	if(env == 0){
		jint ret = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	}
	if( jvm->AttachCurrentThread(&env, NULL) < 0 ){
		LOGE("AttachCurrent Thread failed !!!!");
		return;
	}

	if(surface == 0) {
		LOGE("surface == 0 failed !!!!");
		return;
	}
	if(window == 0){
		window = ANativeWindow_fromSurface(env, surface);
	}
	ANativeWindow_setBuffersGeometry(window, 0, 0, WINDOW_FORMAT_RGBA_8888);
	ANativeWindow_Buffer buffer;
	if (ANativeWindow_lock(window, &buffer, 0) == 0) {
		  memcpy(buffer.bits, data,  width * height * 2);
		  ANativeWindow_unlockAndPost(window);
	}

//	ANativeWindow_release(window);

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
		AVFrame* pFrameRGB = av_frame_alloc();

		// Determine required buffer size and allocate buffer
		int numBytes = avpicture_get_size(AV_PIX_FMT_RGBA,pFrame->width,
				pFrame->height);
		if(yuvbuffer == 0){
			yuvbuffer = (uint8_t*)av_malloc(numBytes*sizeof(uint8_t));
		}


		SwsContext *sws_ctx = sws_getContext(pFrame->width,
				pFrame->height,
				codecCtx->pix_fmt,
				pFrame->width,
				pFrame->height,
				AV_PIX_FMT_RGBA,
				SWS_BILINEAR,
				NULL,NULL,NULL);

		// Assign appropriate parts of buffers to image planes in pFrameRGB
		// Note the pFrameRGB in an AVFrame is a superset of AVPicture
		avpicture_fill((AVPicture*)pFrameRGB,(uint8_t*)yuvbuffer,AV_PIX_FMT_RGBA,
				pFrame->width,pFrame->height);

		// Convert the image from its native format to RGBA
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
	if(yuvbuffer!=0){
		display(yuvbuffer,pFrame->width,pFrame->height,0);
	}

}
