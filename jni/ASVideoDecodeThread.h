/*
 * ASVideoDecodeThread.h
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#ifndef ASVIDEODECODETHREAD_H_
#define ASVIDEODECODETHREAD_H_

extern "C"{
#include<stdio.h>
#include <unistd.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/dict.h>
}
#include "IVideoDecodeCB.h"
//typedef int (*recvDecodeFuncCb)(char* data, int width, int height);

typedef struct VideoDecodeParam{
		AVFormatContext *pFormatCtx;
		int 			 audioStream,videoStream;
		AVCodecContext	*pVideoCodecCtx;
		AVCodec			*pVideoCodec;
		ASVideoDecodeCB *pVideoDecodeFuncCB;
		bool 			*isRunning;
} *pVideoDecodeParam;

class ASVideoDecodeThread {
public:
	ASVideoDecodeThread();
	virtual ~ASVideoDecodeThread();
	void startDecodeThread(VideoDecodeParam *param);
	void stopDecodeThread();
public:
	static void decodeFunc(void *pFormatCtx);
	static bool isRunning;
public:
	VideoDecodeParam *uesedParam;
};

#endif /* ASVIDEODECODETHREAD_H_ */
