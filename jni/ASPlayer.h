/*
 * ASPlayer.h
 *
 *  Created on: 2014-4-13
 *      Author: atomshuai
 */

#ifndef ASPLAYER_H_
#define ASPLAYER_H_

//#ifndef __ANDROID__
//#define __ANDROID__
//#endif

#ifdef __ANDROID__
#include <jni.h>
#endif
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
}

#include <stdio.h>
#include <string>
#include "ASVideoDecodeEvent.h"
#include "ASVideoDecodeThread.h"
class ASNativePlayer{
public:
	static ASNativePlayer* getInstance();
	static ASNativePlayer* createNewInstance();
	static void releaseInstance();
	static void releaseInstance(ASNativePlayer* instance);
public:
	ASNativePlayer();
	~ASNativePlayer();

	int ASOpenFile(char* filename);
	int ASOpenCodec();

	int ASStartVideoDecode();
	int ASStopVideoDecode();

	std::string getMediaSimpleInfo();
	void setVideoDecodeListern(IVideoDecodeCB *handle);
	void setVideoDecodeListern();
	void setDisplayHandle(jobject handle);
public:
	int isOpenFile;
	bool isDecoding;
private:
	static ASNativePlayer* instance;
	AVFormatContext *pFormatCtx;
	int 			 audioStream,videoStream;
	AVCodecContext	*pVideoCodecCtx;
	AVCodec			*pVideoCodec;
	AVDictionary	*videoOptionsDict;

	AVCodecContext	*pAudioCodecCtx;
	AVCodec			*pAudioCodec;
	AVDictionary	*audioOptionsDict;
	FILE			*pSourceFile;
	std::string	    fileName;

	// videoDecodeCallBack
	IVideoDecodeCB	*videoDecodeEeventListern;
	ASVideoDecodeThread		*videoDecodeThread;
	ASVideoDisplay*  videoDisplay;
	pthread_mutex_t decodeMutex;
};


#endif /* ASPLAYER_H_ */
