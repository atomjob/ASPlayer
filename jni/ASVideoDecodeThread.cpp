/*
 * ASVideoDecodeThread.cpp
 *
 *  Created on: 2014-4-20
 *      Author: atomshuai
 */

#include "ASVideoDecodeThread.h"
#include <pthread.h>
ASVideoDecodeThread::ASVideoDecodeThread() :
		uesedParam(0) {

}

ASVideoDecodeThread::~ASVideoDecodeThread() {
	if (uesedParam != 0) {
		delete uesedParam;
		uesedParam = 0;
	}
}

void ASVideoDecodeThread::startDecodeThread(VideoDecodeParam *param) {
	pthread_t tid;
	pthread_create(&tid, NULL,
			(void *(*)(void *))ASVideoDecodeThread::decodeFunc, (void*)param);
		}

void ASVideoDecodeThread::stopDecodeThread() {
}

void ASVideoDecodeThread::decodeFunc(void* args) {
	VideoDecodeParam* videoDecodeParam = (VideoDecodeParam*) args;
	if (videoDecodeParam->pFormatCtx != NULL
			&& videoDecodeParam->pVideoCodecCtx != NULL
			&& videoDecodeParam->pVideoCodec != NULL
			&& videoDecodeParam->videoStream != -1) {

		int i = 0;
		int frameFinished = 0;
		AVPacket packet;
		// Allocate video frame
		AVFrame * pFrame = av_frame_alloc();

			while (av_read_frame(videoDecodeParam->pFormatCtx, &packet) >= 0) {
				pthread_mutex_lock(videoDecodeParam->decodeStateMutex);
					LOGI("==>videoDecodeParam->isRunning = %d",
									*videoDecodeParam->isRunning);
				// Is this a packet from the video stream
				if (packet.stream_index == videoDecodeParam->videoStream) {
					LOGI("==>av_read_frame 02");
					// Decode video frame
					avcodec_decode_video2(videoDecodeParam->pVideoCodecCtx,
							pFrame, &frameFinished, &packet);
					// Did we get a video freame ?
					if (frameFinished) {
						LOGI("==>av_read_frame 03");
						videoDecodeParam->display->display(pFrame,
								videoDecodeParam->pVideoCodecCtx);
					}
				}
				// Free the packet the was allocated by av_read_frame
				av_free_packet(&packet);

				if (!(*videoDecodeParam->isRunning))
					goto exit;
				pthread_mutex_unlock(videoDecodeParam->decodeStateMutex);
			}
			goto exit;
			exit: {
					av_free(pFrame);
					// videoDecodeParam->isRunning = false;
					// exit thread
					// before exit thread should
					JavaVM * g_jvm = videoDecodeParam->display->jvm;
					if (g_jvm != 0) {
					g_jvm->DetachCurrentThread();
					LOGI("exit videoDecode thread");
					if(videoDecodeParam->pVideoDecodeFuncCB!=0){
						videoDecodeParam->pVideoDecodeFuncCB->stopVideoDecoding(true);
					}

					LOGI("after pVideoDecodeFuncCB->stopVideoDecoding");
				}
			}
		}
}
