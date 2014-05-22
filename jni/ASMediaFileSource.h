/*
 * ASMediaHandler.h
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#ifndef ASMEDIAHANDLER_H_
#define ASMEDIAHANDLER_H_
#include "ASCommon.h"
#include "ASVideoInput.h"
#include "ASPacketQueue.h"
#include "ASVideoDecodeProcess.h"
using namespace std;


class ASMediaFileSource : public ASVideoInput{
public:
	ASMediaFileSource();
	~ASMediaFileSource();
    void releaseResource();
public:
    virtual int videoOpen(char *url,VIDEO_SOURCE srcType);
	virtual int videoStart(VideoInputParam *para);
	virtual int videoStop();
	virtual int videoClose();
    
public:
	static void work(void* para);

public:
	AVFormatContext *pFormatCtx;
	int 			 audioStream,videoStream;
	AVCodecContext	*pVideoCodecCtx;
	AVCodec			*pVideoCodec;
	AVDictionary	*videoOptionsDict;

	AVCodecContext	*pAudioCodecCtx;
	AVCodec			*pAudioCodec;
	AVDictionary	*audioOptionsDict;
	FILE			*pSourceFile;
	string          fileName;

	bool 			isVideoAvailable;
	bool 			isAudioAvailable;

	bool 			isRunning;
	pthread_mutex_t decodeMutex;
    pthread_t       work_ptid;
    pthread_mutex_t       pVideoCondMutex;
	pVideoState  videoState;
    
    ASVideoDecodeProcess* pDecodeProcess;

    
    
};

#endif /* ASMEDIAHANDLER_H_ */
