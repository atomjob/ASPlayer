/*
 * ASPlayer.h
 *
 *  Created on: 2014-4-13
 *      Author: atomshuai
 */

#ifndef ASPLAYER_H_
#define ASPLAYER_H_

#ifdef __ANDROID__
#include <jni.h>
#endif
#include "ASLog.h"
#ifndef   UINT64_C
#define   UINT64_C(value)__CONCAT(value,ULL)
#endif
extern "C"{
#include<stdio.h>
#include <unistd.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/dict.h>
}

#include <stdio.h>
#include <string>


class ASNativePlayer{
public:
	static ASNativePlayer* getInstance();
	static void releaseInstance();
public:
	ASNativePlayer();
	~ASNativePlayer();
	int ASOpenFile(char* filename);
	int ASOpenCodec();
	std::string getMediaSimpleInfo();

public:
	int isOpenFile;
//	int isOpenCodec;

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
};


#endif /* ASPLAYER_H_ */
