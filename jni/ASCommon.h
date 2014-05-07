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
	#include <libavcodec/avcodec.h>
	#include <libavformat/avformat.h>
	#include <libswscale/swscale.h>
	#include <libavutil/dict.h>

#ifdef USE_SDL
#include <SDL.h>
#endif
}

#include <string>


#endif /* ASCOMMON_H_ */
