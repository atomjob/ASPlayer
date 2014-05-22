/*
 * ASCommon.h
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#ifndef ASCOMMON_H_
#define ASCOMMON_H_

#ifdef __ANDROID__
#include <jni.h>
#endif

#include "config.h"
#include "ASDefine.h"

#include "ASLog.h"
#ifndef   UINT64_C
#define   UINT64_C(value)__CONCAT(value,ULL)
#endif
extern "C"{
	#include <stdio.h>
	#include <unistd.h>
	#include <pthread.h>
	#include "libavcodec/avcodec.h"
	#include "libavformat/avformat.h"
	#include "libswscale/swscale.h"
    #include "libavutil/avutil.h"
    #include "libavutil/time.h"
	#include "libavutil/dict.h"

#ifdef USE_SDL
//#include <SDL.h>
#endif
}

#include <string>
#include "ASTimer.h"


#define SDL_AUDIO_BUFFER_SIZE 1024
#define MAX_AUDIO_FRAME_SIZE 192000

#define MAX_AUDIOQ_SIZE (5 * 16 * 1024)
#define MAX_VIDEOQ_SIZE (5 * 256 * 1024)
//class ASPacketQueue;
//
//#include "ASPacketQueue.h"



#endif /* ASCOMMON_H_ */
