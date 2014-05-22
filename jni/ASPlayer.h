/*
 * ASPlayer.h
 *
 *  Created on: 2014-4-13
 *      Author: atomshuai
 */

#ifndef ASPLAYER_H_
#define ASPLAYER_H_
#include "ASCommon.h"
#include "ASVideoInput.h"
#include "ASMediaFileSource.h"

enum ASPlayState{
	PLAYER_INIT,
	PLAYER_PAUSED,
	PLAYER_START,
	PLAYER_STOP
};

class ASNativePlayer : public ASVideoInputEvent{
public:
	static ASNativePlayer* createNewInstance();
    static ASNativePlayer* getInstance();
	static void releaseInstance(ASNativePlayer* instance);
    static void releaseInstance();
public:
    static ASNativePlayer* g_instance;
public:
    ASNativePlayer();
	~ASNativePlayer();

	int playVideo(char* filename);
	int stopVideo();

public:
	virtual void videoOpened(VideoInputParam *para);
	virtual void videoStarted(VideoInputParam *para);
	virtual void videoStopped(VideoInputParam *para);
	virtual void videoClosed(VideoInputParam *para);

private:
	ASMediaFileSource* pVideoInput;
    pthread_cond_t playCond;
    pthread_mutex_t playMutex;
    int isPlaying;
public:
	ASPlayState state;
	std::string filename;
};


#endif /* ASPLAYER_H_ */
