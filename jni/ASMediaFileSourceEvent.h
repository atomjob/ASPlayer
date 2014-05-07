/*
 * ASMediaFileSourceEvent.h
 *
 *  Created on: 2014-4-30
 *      Author: atomshuai
 */

#ifndef ASMEDIAFILESOURCEEVENT_H_
#define ASMEDIAFILESOURCEEVENT_H_

#include "ASVideoInput.h"
class ASMediaFileSourceEvent: public ASVideoInputEvent {
public:
	ASMediaFileSourceEvent();
	virtual ~ASMediaFileSourceEvent();
public:
	virtual void videoOpened(VideoInputParam *para);
	virtual void videoStarted(VideoInputParam *para);
	virtual void videoStopped(VideoInputParam *para);
	virtual void videoClosed(VideoInputParam *para);
};

#endif /* ASMEDIAFILESOURCEEVENT_H_ */
