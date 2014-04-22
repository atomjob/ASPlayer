/*
 * ASVideoDecodeEvent.cpp
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#include "ASVideoDecodeEvent.h"

ASVideoDecodeEvent::ASVideoDecodeEvent() :
isStart(0),
isStop(0)
{
	// TODO Auto-generated constructor stub

}

ASVideoDecodeEvent::~ASVideoDecodeEvent() {
	// TODO Auto-generated destructor stub
}

int ASVideoDecodeEvent::startVideoDecoding(bool isStart) {
	printf("=======> isStart : %d\n",isStart);
	return 1;
}

int ASVideoDecodeEvent::stopVideoDecoding(bool isStop) {
	printf("=======> isStop : %d\n",isStop);
	isStart = false;
	return 1;
}


int ASVideoDecodeEvent::recvDecodeData(char* data, int width, int height) {
	return dispayDataOnAndroid(data,width,height);
}

int ASVideoDecodeEvent::dispayDataOnAndroid(char* data, int width,
		int height) {
	// display YUV data on Android
	printf("===> dispay data : width = %d, height = %d\n",width,height);
	LOGI("===> dispay data : width = %d, height = %d\n",width,height);
	return 1;
}

