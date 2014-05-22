/*
 * ASVideoDecodeProcess.h
 *
 *  Created on: 2014-5-3
 *      Author: atomshuai
 */
#ifndef ASVIDEODECODEPROCESS_H_
#define ASVIDEODECODEPROCESS_H_

#include "ASPacketQueue.h"
//#include "ASDisplay.h"




class ASVideoDecodeProcess {

public:
	ASVideoDecodeProcess();
	~ASVideoDecodeProcess();

public:
	void runThread();
	void setVideoState(pVideoState videoState);
    void stopVideoThread();
    void stopAudioThread();
public:
	static void videoDecodeFunc(void* para);
	static void audioDecodeFunc(void* para);
    
    static double synchronizeVideo(VideoState *is, AVFrame *src_frame, double pts);
    static void videoRefreshTimer(void *userdata);
    static int queuePicture(VideoState *is);
    static double getAudioClock(VideoState *is);
public:
	pVideoState videoState;
	pthread_t pVideoThread_d;
	pthread_t pAudioThread_d;
public:
    bool bIsStopVideoDecode;
    bool bIsStopAudioDecode;
    pthread_mutex_t videoStopMutex;
    pthread_mutex_t audioStopMutex;
    
};

#endif /* ASVIDEODECODEPROCESS_H_ */
