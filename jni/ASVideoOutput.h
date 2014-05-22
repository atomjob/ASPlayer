/*
 * ASVideoOutput.h
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#ifndef ASVIDEOOUTPUT_H_
#define ASVIDEOOUTPUT_H_

class ASVideoOutput {
public:
	ASVideoOutput():displayHandler(0){};
	virtual ~ASVideoOutput(){};
	virtual void putFrameQueue(void *frame) = 0;
	virtual int display(unsigned char* data,int width,int height,long size) = 0;
	virtual void setDisplayHandler(void *handler){displayHandler = handler;};

private:
	void *displayHandler;
};

#endif /* ASVIDEOOUTPUT_H_ */
