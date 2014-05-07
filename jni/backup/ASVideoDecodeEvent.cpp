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
