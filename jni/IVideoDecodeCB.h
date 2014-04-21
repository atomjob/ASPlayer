/*
 * ASVideoDecodeCB.h
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#ifndef ASVIDEODECODECB_H_
#define ASVIDEODECODECB_H_
extern "C"{
#include<stdio.h>
#include <unistd.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/dict.h>
}

class ASVideoDecodeCB {
public:
	ASVideoDecodeCB();
	virtual ~ASVideoDecodeCB();
	virtual int startVideoDecoding(bool isStart) = 0;
	virtual int stopVideoDecoding(bool isStop) = 0;
	virtual int recvDecodeData(char *data,int width,int height) =0;
};

#endif /* ASVIDEODECODECB_H_ */
