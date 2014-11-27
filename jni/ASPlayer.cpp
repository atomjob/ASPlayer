/*
 * ASPlayer.cpp
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#include "ASPlayer.h"

ASNativePlayer* ASNativePlayer::g_instance = NULL;

ASNativePlayer* ASNativePlayer::createNewInstance(){
	return new ASNativePlayer();
}

ASNativePlayer* ASNativePlayer::getInstance()
{
	if(!g_instance){
		g_instance = new ASNativePlayer();
	}
	return g_instance;
}

void ASNativePlayer::releaseInstance(ASNativePlayer* instance){
	if(instance){
		delete instance;
		instance = NULL;
	}
}
void ASNativePlayer::releaseInstance(){
	if(g_instance){
		delete g_instance;
		g_instance = NULL;
	}
}


ASNativePlayer::ASNativePlayer():isPlaying(false){
	pVideoInput = new ASMediaFileSource();
	pVideoInput->setEventCB(this);
    pthread_mutex_init(&playMutex, 0);
    pthread_cond_init(&playCond, 0);
}

ASNativePlayer::~ASNativePlayer(){
	if(pVideoInput){
		delete pVideoInput;
		pVideoInput = NULL;
	}
    pthread_mutex_destroy(&playMutex);
    pthread_cond_destroy(&playCond);
}


int ASNativePlayer::playVideo(char* filename){
	LOGI("==>ASNativePlayer::play filename = %s",filename);
//    if(isPlaying)
//        pthread_cond_wait(&playCond, &playMutex);
    pVideoInput->videoOpen(filename, SOURCE_FILE);
	pVideoInput->videoStart(NULL);
	LOGI("ASNativePlayer::play==>");
	return AS_OK;
}
int ASNativePlayer::stopVideo(){
	LOGI("==>NativePlayer::stop");
    pVideoInput->videoStop();
	LOGI("NativePlayer::stop==>");
	return AS_OK;
}

void ASNativePlayer::videoOpened(VideoInputParam *para){
	LOGI("==>ASNativePlayer::videoOpened");
}
void ASNativePlayer::videoStarted(VideoInputParam *para){
	LOGI("==>ASNativePlayer::videoStarted");
//    pthread_mutex_lock(&playMutex);
//    isPlaying = true;
//    pthread_mutex_unlock(&playMutex);
}
void ASNativePlayer::videoStopped(VideoInputParam *para){
	LOGI("==>ASNativePlayer::videoStopped");
	if(para && para->decodeProcess){
        delete para->decodeProcess;
        para->decodeProcess = 0;
    }
    if(para && para->fileSource)
	    	para->fileSource->releaseResource();

}
void ASNativePlayer::videoClosed(VideoInputParam *para){
	LOGI("==>ASNativePlayer::videoClosed");
}

