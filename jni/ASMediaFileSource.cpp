/*
 * ASMediaFileSource.cpp
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#include "ASMediaFileSource.h"


ASMediaFileSource::ASMediaFileSource() :
		pFormatCtx(0), audioStream(-1), videoStream(-1), pVideoCodecCtx(0), pVideoCodec(
				0), videoOptionsDict(0), pAudioCodecCtx(0), pAudioCodec(0), audioOptionsDict(
				0), pSourceFile(0), fileName(), isVideoAvailable(false), isAudioAvailable(
				false), isRunning(false),work_ptid(),nextMediaNode(0) {
	av_register_all();
	pthread_mutex_init(&decodeMutex, 0);
}

ASMediaFileSource::~ASMediaFileSource() {
	releaseResource();
}

void ASMediaFileSource::releaseResource(){
    LOGI("==>ASMediaFileSource::releaseResource");
	if (pVideoCodecCtx != NULL) {
		avcodec_close(pVideoCodecCtx);
		pVideoCodecCtx = NULL;
		LOGI("==>ASMediaFileSource::releaseResource pVideoCodecCtx clean");
	}
    
	if (pAudioCodecCtx != NULL) {
		avcodec_close(pAudioCodecCtx);
		pAudioCodecCtx = NULL;
		LOGI("==>ASMediaFileSource::releaseResource pAudioCodecCtx clean");
	}
    
	if (pFormatCtx != NULL) {
		avformat_close_input(&pFormatCtx);
		LOGI("==>ASMediaFileSource::releaseResource avformat_close_input");
	}
	pthread_mutex_destroy(&decodeMutex);
    isOpen = false;
    isStart = false;
	LOGI("ASMediaFileSource::releaseResource==>");
}

void ASMediaFileSource::work(void* para) {
	ASMediaFileSource* source = (ASMediaFileSource*) para;
	int frameFinished = 0;
	AVPacket packet;
	// Allocate video frame
	AVFrame * pFrame = av_frame_alloc();

	// Is this a packet from the video stream
	while (av_read_frame(source->pFormatCtx, &packet) >= 0) {
		pthread_mutex_lock(&source->decodeMutex);
		if(!source->isRunning){
			goto exit;
		}
		pthread_mutex_unlock(&source->decodeMutex);
		if (packet.stream_index == source->videoStream) {
			// Decode video frame
			avcodec_decode_video2(source->pVideoCodecCtx, pFrame,
					&frameFinished, &packet);
			// Did we get a video frame ?
			if (frameFinished) {
				// send YUV data
				LOGI("==> send raw data width=%d,height=%d\n", pFrame->width,
						pFrame->height);
				source->packetDataRecv(pFrame);
			}
		}
			// Free the packet the was allocated by av_read_frame
			av_free_packet(&packet);
	}
	goto exit;

	exit:{
		LOGI("==> exit work thread");
		av_free_packet(&packet);
		av_free(pFrame);
		source->isRunning = false;
        source->isStart = false;
        source->innerParam.currentState = AS_Stopped;
        source->innerParam.currentActionState = AS_OK;
        source->innerParam.nextAction = AS_Closed;
        source->pEventCB->videoStopped(&source->innerParam);
	}

}

int ASMediaFileSource::packetDataRecv(void* frame) {
	packetDataSend(frame);
	return AS_OK;
}


int ASMediaFileSource::packetDataSend(void* frame) {
	LOGI("===> recv data");
    if(nextMediaNode!=NULL)
        nextMediaNode->packetDataRecv(frame);
	return AS_OK;
}

int ASMediaFileSource::videoOpen(char *filename,VIDEO_SOURCE srcType=SOURCE_FILE){
    this->fileName = fileName;
    innerParam.currentState = AS_Opened;
    innerParam.currentActionState = AS_FAILE;

	if (access(filename, 0) == -1)
		return AS_FAILE;
    
	fileName = filename;
	// open the video file
	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0) {
		return AS_FAILE; // Could't open file
	}
    
	// Retrive stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		return AS_FAILE; // Couldn't find stream information
	}
	// Dump information about file onto standard error
	//av_dump_format(pFormatCtx, 0, filename, 0);
	// Find the first video stream
	videoStream = 1;
	for (int i = 0;
         i < pFormatCtx->nb_streams
         && (videoStream == -1 || audioStream == -1); i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			isVideoAvailable = true;
			continue;
		}
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = i;
			isAudioAvailable = true;
			continue;
		}
	}
	
    if (pFormatCtx == NULL) {
		return AS_FAILE;
	}
    
	if (videoStream != -1) {
		pVideoCodecCtx = pFormatCtx->streams[videoStream]->codec;
	}
    
	if (audioStream != -1) {
		pAudioCodecCtx = pFormatCtx->streams[audioStream]->codec;
	}
    
	// Find the decoder for the video/audio stream
	if (pVideoCodec == NULL) {
		pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
	}
    
	if (pAudioCodec == NULL) {
		pAudioCodec = avcodec_find_decoder(pAudioCodecCtx->codec_id);
	}
    
	if (pAudioCodecCtx != NULL && pAudioCodec != NULL) {
		avcodec_open2(pAudioCodecCtx, pAudioCodec, &audioOptionsDict);
	}
	if (pVideoCodecCtx != NULL && pVideoCodec != NULL) {
		avcodec_open2(pVideoCodecCtx, pVideoCodec, &videoOptionsDict);
	}
	innerParam.currentActionState = AS_OK;
	pEventCB->videoOpened(&innerParam);
	return AS_OK;
}

int ASMediaFileSource::videoStart(VideoInputParam *para){
    if(!isStart){
        pthread_create(&work_ptid, NULL, (void *(*)(void *))ASMediaFileSource::work, (void*)this);
        isRunning = true;
        return AS_OK;
    }
	return AS_FAILE;
}

int ASMediaFileSource::videoStop(){
    printf("==>ASMediaFileSource::videoStop\n");
    pthread_mutex_lock(&decodeMutex);
    isRunning = false;
    pthread_mutex_unlock(&decodeMutex);
    printf("ASMediaFileSource::videoStop==>\n");
    return AS_OK;
}

int ASMediaFileSource::videoClose(){
	if(!isStart && !isRunning){
		releaseResource();
		pEventCB->videoClosed(&innerParam);
	}else{
		videoStop();
	}
    return AS_OK;
}

