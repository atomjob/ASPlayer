/*
 * ASMediaFileSource.cpp
 *
 *  Created on: 2014-4-29
 *      Author: atomshuai
 */

#include "ASMediaFileSource.h"
#include "ASVideoFrameMalloc.h"

ASMediaFileSource::ASMediaFileSource() :
		pFormatCtx(0), audioStream(-1), videoStream(-1), pVideoCodecCtx(0), pVideoCodec(
				0), videoOptionsDict(0), pAudioCodecCtx(0), pAudioCodec(0), audioOptionsDict(
				0), pSourceFile(0), fileName(), isVideoAvailable(false), isAudioAvailable(
				false), isRunning(false), work_ptid() ,videoState(0){
	av_register_all();
	pthread_mutex_init(&decodeMutex, 0);
	pthread_mutex_init(&pVideoCondMutex, 0);
}

ASMediaFileSource::~ASMediaFileSource() {
	releaseResource();
	if (videoState != NULL) {
		delete videoState;
        videoState = 0;
	}
}

void ASMediaFileSource::releaseResource() {
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
    
	//pthread_mutex_destroy(&decodeMutex);
	isOpen = false;
	isStart = false;
	LOGI("ASMediaFileSource::releaseResource==>");
}

void ASMediaFileSource::work(void* para) {
	ASMediaFileSource* source = (ASMediaFileSource*) para;
	AVPacket packet;
        while (av_read_frame(source->pFormatCtx, &packet) >= 0) {
        	LOGI("==>ASMediaFileSource::work (1)");
            bool isGoExit = false;
            pthread_mutex_lock(&source->decodeMutex);
            LOGI("==>ASMediaFileSource::work (2)");
            if (!source->isRunning) {
                isGoExit = true;
                LOGI("==> av_read_frame Thread isGoExit = true");
                source->videoState->videoq.isQuit = true;
            }
            LOGI("==>ASMediaFileSource::work (3)");
            if (isGoExit){
            	pthread_mutex_unlock(&source->decodeMutex);
            	 goto exit;
            }

            LOGI("==>ASMediaFileSource::work (4)");
            pthread_mutex_unlock(&source->decodeMutex);

            if (packet.stream_index == source->videoStream) {
                source->videoState->videoq.put(&packet);
                LOGI("====> (packet.stream_index == source->videoStream)");
            } else if (packet.stream_index == source->audioStream) {
//                source->videoState->audioq.put(&packet);
//                LOGI("====> (packet.stream_index == source->audioStream)");
            }
            //sleep(0.1);
            LOGI("==>ASMediaFileSource::work (5)");
            av_free_packet(&packet);
        }

    
	
	goto exit;

	exit: {
		LOGI("===> ASMediaFileSource goto exit");
		source->isRunning = false;
		source->isStart = false;
//		source->videoState->bIsSourceStop = true;
		pthread_cond_wait(&source->videoState->pVideoDecodeCond,
				&source->pVideoCondMutex);
       
		source->innerParam.currentState = AS_Stopped;
        source->innerParam.fileSource = source;
		source->innerParam.currentActionState = AS_OK;
		source->innerParam.nextAction = AS_Closed;
		LOGI("=====> source->pEventCB->videoStopped");
		source->pEventCB->videoStopped(&source->innerParam);
		LOGI("source->pEventCB->videoStopped=====> ");
		LOGI("ASMediaFileSource goto exit ===>");
	}

}

int ASMediaFileSource::videoOpen(char *filename, VIDEO_SOURCE srcType =
		SOURCE_FILE) {
	LOGI("==>ASMediaFileSource::videoOpen filename = %s",filename);
	this->fileName = fileName;
	innerParam.currentState = AS_Opened;
	innerParam.currentActionState = AS_FAILE;

    if(videoState){
        delete videoState;
        videoState = 0;
    }
    videoState = new VideoState();
    innerParam.videoState = videoState;
    
    
    
	if (access(filename, 0) == -1)
		return AS_FAILE;

	fileName = filename;
	// open the video file
	if (avformat_open_input(&pFormatCtx, filename, NULL, NULL) != 0) {
		return AS_FAILE; // Could't open file
	}
	videoState->pFormatCtx = pFormatCtx;
	// Retrive stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		return AS_FAILE; // Couldn't find stream information
	}
	// Dump information about file onto standard error
	//av_dump_format(pFormatCtx, 0, filename, 0);
	// Find the first video stream
	videoStream = -1;
	for (int i = 0;
			i < pFormatCtx->nb_streams
					&& (videoStream == -1 || audioStream == -1); i++) {
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_VIDEO) {
			videoStream = i;
			videoState->videoStream = videoStream;
			isVideoAvailable = true;

			continue;
		}
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = i;
			videoState->audioStream = audioStream;
			isAudioAvailable = true;
			continue;
		}
	}

	if (pFormatCtx == NULL) {
		return AS_FAILE;
	}

	if (videoStream != -1) {
		pVideoCodecCtx = pFormatCtx->streams[videoStream]->codec;
		videoState->video_st = pFormatCtx->streams[videoStream];

//        videoState->sws_ctx = sws_getContext
//        (
//            videoState->video_st->codec->width,
//            videoState->video_st->codec->height,
//            videoState->video_st->codec->pix_fmt,
//            videoState->video_st->codec->width,
//            videoState->video_st->codec->height,
//            PIX_FMT_YUV420P,
//            SWS_BILINEAR,
//            NULL,
//            NULL,
//            NULL
//         );
		pVideoCodecCtx->get_buffer2 = ASVideoFrameMalloc::get_buffer;
//		          pFormatCtx->streams[i]->codec->release_buffer = ASVideoFrameMalloc::release_buffer;

	}

	if (audioStream != -1) {
		pAudioCodecCtx = pFormatCtx->streams[audioStream]->codec;
		videoState->audio_st = pFormatCtx->streams[audioStream];
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
	LOGI("===>pEventCB->videoOpened");
	pEventCB->videoOpened(&innerParam);
	LOGI("pEventCB->videoOpened===>");
	return AS_OK;
}

int ASMediaFileSource::videoStart(VideoInputParam *para) {
	if (!isStart) {
        isRunning = true;
		if(!pthread_create(&work_ptid, NULL,
				(void *(*)(void *))ASMediaFileSource::work, (void*)this)){
                pDecodeProcess = new ASVideoDecodeProcess();
                innerParam.decodeProcess = pDecodeProcess;
                pDecodeProcess->setVideoState(videoState);
                pDecodeProcess->runThread();
                pEventCB->videoStarted(&innerParam);
                LOGI("ASMediaFileSource::videoStart==>");
                return AS_OK;
            }
        }
            isRunning = false;
			return AS_FAILE;
}

int ASMediaFileSource::videoStop() {
	LOGI("==>ASMediaFileSource::videoStop\n");
	pthread_mutex_lock(&decodeMutex);
	isRunning = false;
    videoState->bIsSourceStop = true;
	pthread_mutex_unlock(&decodeMutex);


	// don't clean this resource before callback function
//    if(pDecodeProcess){
//        delete pDecodeProcess;
//        pDecodeProcess =0;
//    }
//    if(videoState){
//        delete videoState;
//        videoState = 0;
//    }
   // releaseResource();
	LOGI("ASMediaFileSource::videoStop==>\n");
	return AS_OK;
}

int ASMediaFileSource::videoClose() {
	LOGI("==> ASMediaFileSource::videoClose");
	if (!isStart && !isRunning) {
		LOGI("==> ASMediaFileSource::videoClose releaseResource()");
		releaseResource();
		LOGI("ASMediaFileSource::videoClose releaseResource() ==> ");

		LOGI("==> ASMediaFileSource::videoClose pEventCB->videoClosed");
		pEventCB->videoClosed(&innerParam);
		LOGI("ASMediaFileSource::videoClose pEventCB->videoClosed ==>");
	} else {
		videoStop();
	}
	return AS_OK;
}

