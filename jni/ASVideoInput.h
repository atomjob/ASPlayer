/*
 * ASVideoInput.h
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#ifndef ASVIDEOINPUT_H_
#define ASVIDEOINPUT_H_

#include "ASCommon.h"
#include "ASVideoDecodeProcess.h"
//#include "ASMediaFileSource.h"

class ASMediaFileSource;

enum VIDEO_SOURCE{
	SOURCE_FILE,
	SOURCE_NETWORK
};

enum VideoInputState{
	AS_INIT,
	AS_Started,
	AS_Stopped,
	AS_Opened,
	AS_Closed
};

typedef class VideoInputParam{
public:
	int src_width;
	int src_height;
	int dest_width;
	int dest_height;
	int colorSpaceType;
	int currentState; // AS_INIT / AS_Started / AS_Stopped / AS_Opened / AS_Closed
	int currentActionState; // successful / failed
	int nextAction;
	ASVideoDecodeProcess *decodeProcess;
	ASMediaFileSource *fileSource;
//	void *fileSource;
	pVideoState videoState;
public:
    VideoInputParam():
    	src_width(0),src_height(0),
    	dest_width(0),dest_height(0),
    	colorSpaceType(0),currentState(AS_INIT),
    	nextAction(AS_INIT),decodeProcess(0),
    	videoState(0),fileSource(0){}

} *pInputInnerParam;


class ASVideoInput;

class ASVideoInputEvent{
public:
		ASVideoInputEvent(){};
		virtual ~ASVideoInputEvent(){};
		virtual void videoOpened(VideoInputParam *para) = 0;
		virtual void videoStarted(VideoInputParam *para) = 0;
		virtual void videoStopped(VideoInputParam *para) = 0;
		virtual void videoClosed(VideoInputParam *para) = 0;
};

class ASVideoInput {
public:
	ASVideoInput()
        :pEventCB(0),innerParam(),isStart(false),isOpen(false){};
	virtual ~ASVideoInput(){};
	virtual int videoOpen(char *url,VIDEO_SOURCE srcType) = 0;
	virtual int videoStart(VideoInputParam *para) = 0;
	virtual int videoStop() = 0;
	virtual int videoClose() = 0;
	
	void setEventCB(ASVideoInputEvent *eventCB){
		this->pEventCB = eventCB;
	}
public:
	ASVideoInputEvent *pEventCB;
    VideoInputParam  innerParam;
    bool isStart;
    bool isOpen;
};

#endif /* ASVIDEOINPUT_H_ */