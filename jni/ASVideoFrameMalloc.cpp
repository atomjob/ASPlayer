/*
 * ASVideoFrameMalloc.cpp
 *
 *  Created on: 2014-5-5
 *      Author: atomshuai
 */

#include "ASVideoFrameMalloc.h"

uint64_t ASVideoFrameMalloc::global_video_pkt_pts = AV_NOPTS_VALUE;

int ASVideoFrameMalloc::get_buffer(struct AVCodecContext* c, AVFrame* pic) {
	int rect = avcodec_default_get_buffer2(c,pic,0);
	uint64_t *pts = (uint64_t *)av_malloc(sizeof(uint64_t));
	*pts = global_video_pkt_pts;
	pic->opaque = pts;
	return rect;
}

void ASVideoFrameMalloc::release_buffer(struct AVCodecContext* c,
		AVFrame* pic) {
	if(pic) av_freep(&pic->opaque);
	  avcodec_default_release_buffer(c, pic);
}
