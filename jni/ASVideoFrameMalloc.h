/*
 * ASVideoFrameMalloc.h
 *
 *  Created on: 2014-5-5
 *      Author: atomshuai
 */

#ifndef ASVIDEOFRAMEMALLOC_H_
#define ASVIDEOFRAMEMALLOC_H_
#include "ASCommon.h"



class ASVideoFrameMalloc {
public:
	static int get_buffer(struct AVCodecContext *c, AVFrame *pic);
	static void release_buffer(struct AVCodecContext *c, AVFrame *pic);
public:
	static uint64_t global_video_pkt_pts;
};

#endif /* ASVIDEOFRAMEMALLOC_H_ */
