/*
 * ASNativeAudio.h
 *
 *  Created on: 2014-5-7
 *      Author: atomshuai
 */

#ifndef ASNATIVEAUDIO_H_
#define ASNATIVEAUDIO_H_

#include <assert.h>
#include <jni.h>
#include <string.h>

#include "ASLog.h"
// for __android_log_print(ANDROID_LOG_INFO, "YourApp", "formatted message");
// #include <android/log.h>

// for native audio
#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>

// for native asset manager
#include <sys/types.h>
#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

//static const char hello[] =
////#include "hello_clip.h"
//;

//static const char android[] =
////#include "android_clip.h"
//;

class ASNativeAudio{
	public:
		// engine interfaces
		 SLObjectItf engineObject;
		 SLEngineItf engineEngine;

		// output mix interfaces
		SLObjectItf outputMixObject;
		SLEnvironmentalReverbItf outputMixEnvironmentalReverb;

		// buffer queue player interfaces
		SLObjectItf bqPlayerObject ;
		SLPlayItf bqPlayerPlay;
		SLAndroidSimpleBufferQueueItf bqPlayerBufferQueue;
		SLEffectSendItf bqPlayerEffectSend;
		SLMuteSoloItf bqPlayerMuteSolo;
		SLVolumeItf bqPlayerVolume;

		// aux effect on the output mix, used by the buffer queue player
		const SLEnvironmentalReverbSettings reverbSettings;

		// URI player interfaces
//		 SLObjectItf uriPlayerObject = NULL;
//		 SLPlayItf uriPlayerPlay;
//		 SLSeekItf uriPlayerSeek;
//		 SLMuteSoloItf uriPlayerMuteSolo;
//		 SLVolumeItf uriPlayerVolume;

		// file descriptor player interfaces
		 SLObjectItf fdPlayerObject;
		 SLPlayItf fdPlayerPlay;
		 SLSeekItf fdPlayerSeek;
		 SLMuteSoloItf fdPlayerMuteSolo;
		 SLVolumeItf fdPlayerVolume;

		// recorder interfaces
		 SLObjectItf recorderObject;
		 SLRecordItf recorderRecord;
		 SLAndroidSimpleBufferQueueItf recorderBufferQueue;

		// synthesized sawtooth clip
		#define SAWTOOTH_FRAMES 8000
		short sawtoothBuffer[SAWTOOTH_FRAMES];

		// 5 seconds of recorded audio at 16 kHz mono, 16-bit signed little endian
		#define RECORDER_FRAMES (16000 * 5)
		 short recorderBuffer[RECORDER_FRAMES];
		 unsigned recorderSize;
		 SLmilliHertz recorderSR;

		// pointer and size of the next player buffer to enqueue, and number of remaining buffers
		 short *nextBuffer;
		 unsigned nextSize;
		 int nextCount;


public:
		 __attribute__((constructor))  void onDlOpen(void)
		{
		    unsigned i;
		    for (i = 0; i < SAWTOOTH_FRAMES; ++i) {
		        sawtoothBuffer[i] = 32768 - ((i % 100) * 660);
		    }
		}

public:
		// this callback handler is called every time a buffer finishes playing
		static void bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq, void *context);
//		static void bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq, void *context);

public:
		ASNativeAudio();
		void NativeAudio_createEngine();
		void NativeAudio_createBufferQueueAudioPlayer();
		void NativeAudio_shutdown();
		void putAudioPacket();
};

#endif /* ASNATIVEAUDIO_H_ */
