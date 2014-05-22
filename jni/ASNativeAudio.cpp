/*
 * ASNativeAudio.cpp
 *
 *  Created on: 2014-5-7
 *      Author: atomshuai
 */

#include "ASNativeAudio.h"

ASNativeAudio::ASNativeAudio()
:engineObject(NULL),engineEngine(NULL),outputMixObject(NULL),
outputMixEnvironmentalReverb(NULL),bqPlayerObject(NULL),
bqPlayerPlay(NULL),bqPlayerBufferQueue(NULL),bqPlayerEffectSend(NULL),
bqPlayerMuteSolo(NULL),bqPlayerVolume(NULL),fdPlayerObject(NULL),
fdPlayerPlay(NULL),fdPlayerSeek(NULL),fdPlayerMuteSolo(NULL),
fdPlayerVolume(NULL),recorderObject(NULL),recorderRecord(NULL),
recorderBufferQueue(NULL),nextBuffer(NULL),nextSize(0),
nextCount(0),reverbSettings(SL_I3DL2_ENVIRONMENT_PRESET_STONECORRIDOR)
{
	NativeAudio_createEngine();
	NativeAudio_createBufferQueueAudioPlayer();
}

void ASNativeAudio::bqPlayerCallback(SLAndroidSimpleBufferQueueItf bq,
		void* context) {
	LOGI("==> bqPlayerCallback");
	ASNativeAudio* nativeAudio = NULL;
	if(context==0) return;

		nativeAudio = (ASNativeAudio*)context;
	    assert(bq == bqPlayerBufferQueue);
	    assert(NULL == nativeAudio);

	    // for streaming playback, replace this test by logic to find and fill the next buffer
	    if (--(nativeAudio->nextCount) > 0 && NULL != nativeAudio->nextBuffer && 0 != nativeAudio->nextSize) {
	        SLresult result;
	        // enqueue another buffer
	        result = (*(nativeAudio->bqPlayerBufferQueue))->Enqueue(nativeAudio->bqPlayerBufferQueue, nativeAudio->nextBuffer, nativeAudio->nextSize);
	        // the most likely other result is SL_RESULT_BUFFER_INSUFFICIENT,
	        // which for this code example would indicate a programming error
	        assert(SL_RESULT_SUCCESS == result);
	        (void)result;
	    }
	    LOGI("bqPlayerCallback==>");
}

//void ASNativeAudio::bqRecorderCallback(SLAndroidSimpleBufferQueueItf bq,
//		void* context) {
//	LOGI("==> bqRecorderCallback");
//    assert(bq == bqRecorderBufferQueue);
//    assert(NULL == context);
//    // for streaming recording, here we would call Enqueue to give recorder the next buffer to fill
//    // but instead, this is a one-time buffer so we stop recording
//    SLresult result;
//    result = (*recorderRecord)->SetRecordState(recorderRecord, SL_RECORDSTATE_STOPPED);
//    if (SL_RESULT_SUCCESS == result) {
//        recorderSize = RECORDER_FRAMES * sizeof(short);
//        recorderSR = SL_SAMPLINGRATE_16;
//    }
//    LOGI("bqRecorderCallback==>");
//}

void ASNativeAudio::NativeAudio_createEngine() {
	LOGI("==> Java_com_example_nativeaudio_NativeAudio_createEngine");
	    SLresult result;

	    // create engine
	    result = slCreateEngine(&engineObject, 0, NULL, 0, NULL, NULL);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // realize the engine
	    result = (*engineObject)->Realize(engineObject, SL_BOOLEAN_FALSE);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the engine interface, which is needed in order to create other objects
	    result = (*engineObject)->GetInterface(engineObject, SL_IID_ENGINE, &engineEngine);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // create output mix, with environmental reverb specified as a non-required interface
	    const SLInterfaceID ids[1] = {SL_IID_ENVIRONMENTALREVERB};
	    const SLboolean req[1] = {SL_BOOLEAN_FALSE};
	    result = (*engineEngine)->CreateOutputMix(engineEngine, &outputMixObject, 1, ids, req);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // realize the output mix
	    result = (*outputMixObject)->Realize(outputMixObject, SL_BOOLEAN_FALSE);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the environmental reverb interface
	    // this could fail if the environmental reverb effect is not available,
	    // either because the feature is not present, excessive CPU load, or
	    // the required MODIFY_AUDIO_SETTINGS permission was not requested and granted
	    result = (*outputMixObject)->GetInterface(outputMixObject, SL_IID_ENVIRONMENTALREVERB,
	            &outputMixEnvironmentalReverb);
	    if (SL_RESULT_SUCCESS == result) {
	        result = (*outputMixEnvironmentalReverb)->SetEnvironmentalReverbProperties(
	                outputMixEnvironmentalReverb, &reverbSettings);
	        (void)result;
	    }
	    // ignore unsuccessful result codes for environmental reverb, as it is optional for this example
	    LOGI("Java_com_example_nativeaudio_NativeAudio_createEngine==> ");
}

void ASNativeAudio::NativeAudio_createBufferQueueAudioPlayer() {
	LOGI("==> Java_com_example_nativeaudio_NativeAudio_createBufferQueueAudioPlayer");
	    SLresult result;

	    // configure audio source
	    SLDataLocator_AndroidSimpleBufferQueue loc_bufq = {SL_DATALOCATOR_ANDROIDSIMPLEBUFFERQUEUE, 2};
	    SLDataFormat_PCM format_pcm = {SL_DATAFORMAT_PCM, 1, SL_SAMPLINGRATE_8,
	        SL_PCMSAMPLEFORMAT_FIXED_16, SL_PCMSAMPLEFORMAT_FIXED_16,
	        SL_SPEAKER_FRONT_CENTER, SL_BYTEORDER_LITTLEENDIAN};
	    SLDataSource audioSrc = {&loc_bufq, &format_pcm};

	    // configure audio sink
	    SLDataLocator_OutputMix loc_outmix = {SL_DATALOCATOR_OUTPUTMIX, outputMixObject};
	    SLDataSink audioSnk = {&loc_outmix, NULL};

	    // create audio player
	    const SLInterfaceID ids[3] = {SL_IID_BUFFERQUEUE, SL_IID_EFFECTSEND,
	            /*SL_IID_MUTESOLO,*/ SL_IID_VOLUME};
	    const SLboolean req[3] = {SL_BOOLEAN_TRUE, SL_BOOLEAN_TRUE,
	            /*SL_BOOLEAN_TRUE,*/ SL_BOOLEAN_TRUE};
	    result = (*engineEngine)->CreateAudioPlayer(engineEngine, &bqPlayerObject, &audioSrc, &audioSnk,
	            3, ids, req);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // realize the player
	    result = (*bqPlayerObject)->Realize(bqPlayerObject, SL_BOOLEAN_FALSE);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the play interface
	    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_PLAY, &bqPlayerPlay);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the buffer queue interface
	    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_BUFFERQUEUE,
	            &bqPlayerBufferQueue);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // register callback on the buffer queue
	    result = (*bqPlayerBufferQueue)->RegisterCallback(bqPlayerBufferQueue, bqPlayerCallback, this);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // get the effect send interface
	    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_EFFECTSEND,
	            &bqPlayerEffectSend);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	#if 0   // mute/solo is not supported for sources that are known to be mono, as this is
	    // get the mute/solo interface
	    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_MUTESOLO, &bqPlayerMuteSolo);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;
	#endif

	    // get the volume interface
	    result = (*bqPlayerObject)->GetInterface(bqPlayerObject, SL_IID_VOLUME, &bqPlayerVolume);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;

	    // set the player's state to playing
	    result = (*bqPlayerPlay)->SetPlayState(bqPlayerPlay, SL_PLAYSTATE_PLAYING);
	    assert(SL_RESULT_SUCCESS == result);
	    (void)result;
	    LOGI("Java_com_example_nativeaudio_NativeAudio_createBufferQueueAudioPlayer==> ");
}

void ASNativeAudio::NativeAudio_shutdown() {
	  // destroy buffer queue audio player object, and invalidate all associated interfaces
	    if (bqPlayerObject != NULL) {
	        (*bqPlayerObject)->Destroy(bqPlayerObject);
	        bqPlayerObject = NULL;
	        bqPlayerPlay = NULL;
	        bqPlayerBufferQueue = NULL;
	        bqPlayerEffectSend = NULL;
	        bqPlayerMuteSolo = NULL;
	        bqPlayerVolume = NULL;
	    }

	    // destroy file descriptor audio player object, and invalidate all associated interfaces
	    if (fdPlayerObject != NULL) {
	        (*fdPlayerObject)->Destroy(fdPlayerObject);
	        fdPlayerObject = NULL;
	        fdPlayerPlay = NULL;
	        fdPlayerSeek = NULL;
	        fdPlayerMuteSolo = NULL;
	        fdPlayerVolume = NULL;
	    }

	    // destroy URI audio player object, and invalidate all associated interfaces
//	    if (uriPlayerObject != NULL) {
//	        (*uriPlayerObject)->Destroy(uriPlayerObject);
//	        uriPlayerObject = NULL;
//	        uriPlayerPlay = NULL;
//	        uriPlayerSeek = NULL;
//	        uriPlayerMuteSolo = NULL;
//	        uriPlayerVolume = NULL;
//	    }

	    // destroy audio recorder object, and invalidate all associated interfaces
	    if (recorderObject != NULL) {
	        (*recorderObject)->Destroy(recorderObject);
	        recorderObject = NULL;
	        recorderRecord = NULL;
	        recorderBufferQueue = NULL;
	    }

	    // destroy output mix object, and invalidate all associated interfaces
	    if (outputMixObject != NULL) {
	        (*outputMixObject)->Destroy(outputMixObject);
	        outputMixObject = NULL;
	        outputMixEnvironmentalReverb = NULL;
	    }

	    // destroy engine object, and invalidate all associated interfaces
	    if (engineObject != NULL) {
	        (*engineObject)->Destroy(engineObject);
	        engineObject = NULL;
	        engineEngine = NULL;
	    }
}
