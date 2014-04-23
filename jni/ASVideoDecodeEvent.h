/*
 * ASVideoDecodeEventImp.h
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#ifndef ASVIDEODECODEEVENTIMP_H_
#define ASVIDEODECODEEVENTIMP_H_
#include "ASLog.h"
#include "IVideoDecodeCB.h"

class ASVideoDecodeEvent : public IVideoDecodeCB{
public:
	ASVideoDecodeEvent();
	~ASVideoDecodeEvent();

	virtual int startVideoDecoding(bool isStart);
	virtual int stopVideoDecoding(bool isStop);
//	virtual int recvDecodeData(char *data,int width,int height);
//	virtual int dispayDataOnAndroid(char *data,int width,int height);

public:
	bool isStart;
	bool isStop;
};

#endif /* ASVIDEODECODEEVENTIMP_H_ */
