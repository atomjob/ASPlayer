/*
 * ASVideoDecodeThread.cpp
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#include "ASVideoDecodeThread.h"
#include <pthread.h>
ASVideoDecodeThread::ASVideoDecodeThread():
uesedParam(0){
	// TODO Auto-generated constructor stub

}

ASVideoDecodeThread::~ASVideoDecodeThread() {
	// TODO Auto-generated destructor stub
	if(uesedParam!=0){
		delete uesedParam;
		uesedParam = 0;
	}
}

void ASVideoDecodeThread::startDecodeThread(VideoDecodeParam *param) {
	pthread_t tid;
	pthread_create(&tid,NULL,(void *(*)(void *))ASVideoDecodeThread::decodeFunc,(void*)param);
}

void ASVideoDecodeThread::stopDecodeThread() {
}

void ASVideoDecodeThread::decodeFunc(void* args) {
	VideoDecodeParam* videoDecodeParam = (VideoDecodeParam*)args;
	if(videoDecodeParam->pFormatCtx!=NULL &&
			videoDecodeParam->pVideoCodecCtx!=NULL &&
			videoDecodeParam->pVideoCodec!=NULL &&
			videoDecodeParam->videoStream !=-1){

			int i = 0;
			int frameFinished = 0;
			AVPacket packet;
			// Allocate video frame
			AVFrame * pFrame = av_frame_alloc();

				while(videoDecodeParam != 0 &&
						av_read_frame(videoDecodeParam->pFormatCtx,&packet)>=0 &&
						videoDecodeParam->isRunning){
					// Is this a packet from the video stream
					if(packet.stream_index == videoDecodeParam->videoStream){
						// Decode video frame
						avcodec_decode_video2(videoDecodeParam->pVideoCodecCtx,pFrame,&frameFinished,
								&packet);
						// Did we get a video freame ?
						if(frameFinished){
							// Convert the image from its native format to RGB
							 /*sws_scale(sws_ctx,(uint8_t const * const *)pFrame->data,
									pFrame->linesize,0,
									pCodecCtx->height,
									pFrameRGB->data,
									pFrameRGB->linesize);
							*/
							// save the frame to disk
							videoDecodeParam->pVideoDecodeFuncCB->recvDecodeData((char*)pFrame->data,pFrame->width,pFrame->height);
						}
					}

					// Free the packet the was allocated by av_read_frame
					av_free_packet(&packet);
				}
				videoDecodeParam->pVideoDecodeFuncCB->stopVideoDecoding(true);
				videoDecodeParam->isRunning = false;

	}

}
