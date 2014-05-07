/*
 * ASPlayer.cpp
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#include "ASPlayer.h"
ASNativePlayer::ASNativePlayer() :
state(PLAYER_INIT),pVideoInput(NULL),pVideoInputEvent(NULL){
}

ASNativePlayer::ASNativePlayer(std::string filename) :
		state(PLAYER_INIT),pVideoInput(NULL),pVideoInputEvent(NULL){
	pVideoInput = new ASMediaFileSource();
	this->filename = filename;
//	pVideoInputEvent = new ASMediaFileSourceEvent();
//	pVideoInput->setEventCB((ASVideoInputEvent*) pVideoInputEvent);
//	pVideoInput->videoOpen((char *) filename.c_str(), SOURCE_FILE);
}

ASNativePlayer* ASNativePlayer::createNewInstance(){
	return new ASNativePlayer();
}

ASNativePlayer* ASNativePlayer::createNewInstance(char* filename) {
	return new ASNativePlayer(filename);
}

void ASNativePlayer::releaseInstance(ASNativePlayer* instance) {
	if (instance != 0) {
		delete instance;
		instance = 0;
	}
}

ASNativePlayer::~ASNativePlayer() {
	if (pVideoInput != 0) {
		delete pVideoInput;
		pVideoInput = 0;
	}
	if(pVideoInputEvent != 0){
		delete pVideoInputEvent;
		pVideoInputEvent = 0;
	}
}

void ASNativePlayer::setVideoInputListener(ASVideoInputEvent* eventListener) {
	this->pVideoInputEvent = eventListener;
	pVideoInput->setEventCB(eventListener);
}

int ASNativePlayer::play() {
	LOGI("==>ASNativePlayer::play");
	if(pVideoInputEvent == NULL){
			pVideoInputEvent = new ASMediaFileSourceEvent();
			pVideoInput->setEventCB((ASVideoInputEvent*) pVideoInputEvent);
	}
	pVideoInput->videoOpen((char *) filename.c_str(), SOURCE_FILE);
	pVideoInput->videoStart(NULL);
	LOGI("ASNativePlayer::play==>");
	return AS_OK;
}

int ASNativePlayer::stop() {
	pVideoInput->videoStop();
	return AS_OK;
}

int ASNativePlayer::pause() {
	return AS_OK;
}

int ASNativePlayer::end() {
	return AS_OK;
}

