/*
 * ASMediaFileSourceEvent.cpp
 *
 *  Created on: 2014-4-30
 *      Author: atomshuai
 */

#include "ASMediaFileSourceEvent.h"

ASMediaFileSourceEvent::ASMediaFileSourceEvent() {

}

ASMediaFileSourceEvent::~ASMediaFileSourceEvent() {
}

void ASMediaFileSourceEvent::videoOpened(VideoInputParam* para) {
	LOGI("===> ASMediaFileSourceEvent::videoOpened\n");
}

void ASMediaFileSourceEvent::videoStarted(VideoInputParam* para) {
	LOGI("===> ASMediaFileSourceEvent::videoStarted\n");
}

void ASMediaFileSourceEvent::videoStopped(VideoInputParam *para) {
	LOGI("===> ASMediaFileSourceEvent::videoStopped\n");

	// When recv the stopped state, Do videoClose() functoin
	if(para->nextAction == AS_Closed
			&& para->currentState == AS_Stopped
			&& para->currentActionState == AS_OK){
		this->videoInputInstance->videoClose();
	}
}

void ASMediaFileSourceEvent::videoClosed(VideoInputParam *para) {
	LOGI("===> ASMediaFileSourceEvent::videoClosed\n");
}
