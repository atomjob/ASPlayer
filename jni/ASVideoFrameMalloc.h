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
	/* These are called whenever we allocate a frame
	 * buffer. We use this to store the global_pts in
	 * a frame at the time it is allocated.
	 */
	static int get_buffer(struct AVCodecContext *c, AVFrame *pic,int flag);


	static void release_buffer(struct AVCodecContext *c, AVFrame *pic);
public:
	static uint64_t global_video_pkt_pts;
};

#endif /* ASVIDEOFRAMEMALLOC_H_ */
