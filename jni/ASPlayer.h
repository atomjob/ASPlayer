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
#include "ASVideoOutput.h"
#include "ASMediaFileSourceEvent.h"
#include "ASMediaFileSource.h"

enum ASPlayState{
	PLAYER_INIT,
	PLAYER_PAUSED,
	PLAYER_START,
	PLAYER_STOP
};

class ASNativePlayer{
public:
	static ASNativePlayer* createNewInstance();
	static ASNativePlayer* createNewInstance(char* filename);
	static void releaseInstance(ASNativePlayer* instance);
public:
	ASNativePlayer(std::string filename);
    ASNativePlayer();
	~ASNativePlayer();

	int play();
	int stop();
	int pause();
	int end();

	void setVideoInputListener(ASVideoInputEvent* eventListener);

private:
	ASMediaFileSource* pVideoInput;
//	ASMediaFileSourceEvent* pVideoInputEvent;
	ASVideoInputEvent	*pVideoInputEvent;
public:
	ASPlayState state;
	std::string filename;
};


#endif /* ASPLAYER_H_ */
