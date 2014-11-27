/*
 * ASDisplay.cpp
 *
 *  Created on: 2014-5-3
 *      Author: atomshuai
 */

#include "ASDisplay.h"




ASDisplay::ASDisplay():
	yuvbuffer(0), width_output(0), heigth_output(0) {
#ifdef __ANDROID__
	env = JNI_GetEnv();
	jvm = JNI_GetVM();
	window = 0;
#endif{
}

ASDisplay::~ASDisplay() {
	/*window = ANativeWindow_fromSurface(env, surface);*/
		if (window != 0) {
			ANativeWindow_release (window);
			window = 0;
		}
		av_free(yuvbuffer);
}

int ASDisplay::display(unsigned char* data, int width, int height, long size) {
#ifdef __ANDROID__
	LOGI("===> ASVideoDisplay::display");
	if(jvm == 0) {
		LOGI("===> ASVideoDisplay::display jvm == 0");
		return 0;
	}
	jint ret;
	//Should AttachCurrentThread if not cause JNI ERROR: non-VM thread making JNI call
	if(env == 0) {
		ret = jvm->GetEnv((void **)&env, JNI_VERSION_1_6);
	}
	if(ret<0)
	{
		LOGI("===> ASVideoDisplay::get jvm->GetEnv failed");
		return ret;
	}
	if(ret = (jvm->AttachCurrentThread(&env, NULL)) < 0 ) {
		LOGE("AttachCurrent Thread failed !!!!");
		return ret;
	}

	if(surface == 0) {
		LOGE("surface == 0 failed !!!!");
		return -1;
	}
	if(window == 0) {
		window = ANativeWindow_fromSurface(env, surface);
	}
	if(window == 0) return -1;

	ANativeWindow_setBuffersGeometry(window, 0, 0, WINDOW_FORMAT_RGBA_8888);
	ANativeWindow_Buffer buffer;
	if (ANativeWindow_lock(window, &buffer, 0) == 0) {
		memcpy(buffer.bits, data, heigth_output * width_output * 4);
		ANativeWindow_unlockAndPost(window);
	}

	return 1;
//	ANativeWindow_release(window);

#endif
}

#ifdef __ANDROID__
void ASDisplay::setDisplayHandle(jobject surface) {
	if(surface != 0) {
		this->surface = surface;
	}
#endif
}
