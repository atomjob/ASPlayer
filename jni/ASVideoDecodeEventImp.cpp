/*
 * ASVideoDecodeEventImp.cpp
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#include "ASVideoDecodeEventImp.h"

ASVideoDecodeEventImp::ASVideoDecodeEventImp() :
isStart(0),
isStop(0){
	// TODO Auto-generated constructor stub

}

ASVideoDecodeEventImp::~ASVideoDecodeEventImp() {
	// TODO Auto-generated destructor stub
}

int ASVideoDecodeEventImp::startVideoDecoding(bool isStart) {
	printf("=======> isStart : %d\n",isStart);
	return 1;
}

int ASVideoDecodeEventImp::stopVideoDecoding(bool isStop) {
	printf("=======> isStop : %d\n",isStop);
	isStart = false;
	return 1;
}


int ASVideoDecodeEventImp::recvDecodeData(char* data, int width, int height) {
	return dispayDataOnAndroid(data,width,height);
}

int ASVideoDecodeEventImp::dispayDataOnAndroid(char* data, int width,
		int height) {
	// display YUV data on Android
	printf("===> dispay data : width = %d, height = %d\n",width,height);
	return 1;
}
