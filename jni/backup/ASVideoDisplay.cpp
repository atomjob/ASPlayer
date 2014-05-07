/*
 * ASVideoDisplay.cpp
 *
 *  Created on: 2014-4-22
 *      Author: atomshuai
 */

#include "ASVideoDisplay.h"
#include <string.h>

ASVideoDisplay::ASVideoDisplay() :
		yuvbuffer(0), width_output(0), heigth_output(0) {
#ifdef __ANDROID__
	env = JNI_GetEnv();
	jvm = JNI_GetVM();
	window = 0;
#endif
}

ASVideoDisplay::~ASVideoDisplay() {

	/*window = ANativeWindow_fromSurface(env, surface);*/
	if (window != 0) {
		ANativeWindow_release (window);
		window = 0;
	}
	if (surface != 0) {
		/*
		 LOGI("===>~ASVideoDisplay surface!=0");
		 if(env!=0){
		 env->DeleteGlobalRef(surface);
		 LOGI("===>~ASVideoDisplay surface!=0 env!=0");
		 }
		 LOGI("===>~ASVideoDisplay surface!=0 env==0");
		 LOGI("~ASVideoDisplay surface!=0 ===> ");
		 */
	}
	av_free(yuvbuffer);
}

void ASVideoDisplay::display(void* data, int height, int width, int size) {
#ifdef __ANDROID__
	LOGI("===> ASVideoDisplay::display");
	if(jvm == 0) {
		LOGI("===> ASVideoDisplay::display jvm == 0");
		return;
	}
	jint ret;
	//Should AttachCurrentThread if not cause JNI ERROR: non-VM thread making JNI call
	if(env == 0) {
		ret = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	}
	if(ret<0)
	{
		LOGI("===> ASVideoDisplay::get jvm->GetEnv failed");
		return;
	}
	if(jvm->AttachCurrentThread(&env, NULL) < 0 ) {
		LOGE("AttachCurrent Thread failed !!!!");
		return;
	}

	if(surface == 0) {
		LOGE("surface == 0 failed !!!!");
		return;
	}
	if(window == 0) {
		window = ANativeWindow_fromSurface(env, surface);
	}
	if(window == 0) return;

	ANativeWindow_setBuffersGeometry(window, 0, 0, WINDOW_FORMAT_RGBA_8888);
	ANativeWindow_Buffer buffer;
	if (ANativeWindow_lock(window, &buffer, 0) == 0) {
		memcpy(buffer.bits, data, heigth_output * width_output * 4);
		ANativeWindow_unlockAndPost(window);
	}

//	ANativeWindow_release(window);

#endif
}
#ifdef __ANDROID__
void ASVideoDisplay::setDisplayHandle(jobject surface) {
	if(surface != 0) {
		this->surface = surface;
	}
}
#endif
AVFrame* ASVideoDisplay::convertColorAndResize(AVFrame* pFrame,
		AVCodecContext *codecCtx) {
	AVFrame* pFrameRGB = av_frame_alloc();

	int width_window = 0;
	int height_window = 0;
//		int width_output = 0;
//		int heigth_output = 0;

	width_output= pFrame->width;
	heigth_output = pFrame->height;

	float screen_radio = 0;

//	if (window != 0) {
//		getDestScreen(&width_window, &height_window);
		width_window = 1280;
		height_window = 720;
		if (pFrame->width > width_window || pFrame->height > height_window) {
			float radio = (float) width_window / (float) height_window;
//			width_output = pFrame->width / radio;
//			heigth_output = pFrame->height / radio;
			width_output = 1280;
			heigth_output = 720;
		}
//	}
	LOGI("heigth_output = %d, heigth_output=%d, width_window=%d, height_window=%d"
			,width_output,heigth_output,width_window,height_window);

	int numBytes = avpicture_get_size(AV_PIX_FMT_RGBA, width_output,
			heigth_output);
	if (yuvbuffer == 0) {
		yuvbuffer = (uint8_t*) av_malloc(numBytes * sizeof(uint8_t));
	}

	LOGI("video Frame width=%d, height=%d", pFrame->width, pFrame->height);
	SwsContext *sws_ctx = sws_getContext(pFrame->width, pFrame->height,
			codecCtx->pix_fmt, width_output, heigth_output, AV_PIX_FMT_RGBA,
			SWS_BILINEAR, NULL, NULL, NULL);

	// Assign appropriate parts of buffers to image planes in pFrameRGB
	// Note the pFrameRGB in an AVFrame is a superset of AVPicture
	avpicture_fill((AVPicture*) pFrameRGB, (uint8_t*) yuvbuffer,
			AV_PIX_FMT_RGBA, width_output, heigth_output);

	// Convert the image from its native format to RGBA
	sws_scale(sws_ctx, (uint8_t const * const *) pFrame->data, pFrame->linesize,
			0, pFrame->height, pFrameRGB->data, pFrameRGB->linesize);
	sws_freeContext(sws_ctx);
}

void ASVideoDisplay::display(AVFrame* pFrame, AVCodecContext *codecCtx) {
	if (pFrame == 0)
		return;
	AVFrame* pFrameRGB = convertColorAndResize(pFrame, codecCtx);
	if (yuvbuffer != 0) {
		display(yuvbuffer, pFrame->width, pFrame->height, 0);
	}

}

void ASVideoDisplay::getDestScreen(int* width, int* heigth) {
#ifdef __ANDROID__
	if(window!=0) {
		*width = ANativeWindow_getWidth(window);
		*heigth = ANativeWindow_getHeight(window);
		LOGI("ASVideoDisplay::getDestScreen window width=%d height=%d",*width,*heigth);
	}
#endif
}


