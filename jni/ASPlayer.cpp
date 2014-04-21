#include "ASPlayer.h"

ASNativePlayer* ASNativePlayer::instance = NULL;
ASNativePlayer* ASNativePlayer::getInstance() {
	if (instance == NULL) {
		instance = new ASNativePlayer();
	}
	return instance;
}

void ASNativePlayer::releaseInstance() {
	if (instance != NULL) {
		delete instance;
		instance = NULL;
	}
}

ASNativePlayer::ASNativePlayer() :
		pFormatCtx(NULL),
		audioStream(-1),
		videoStream(-1),
		pVideoCodecCtx(NULL),
		pVideoCodec(NULL),
		pAudioCodecCtx(NULL),
		pAudioCodec(NULL),
		pSourceFile(NULL),
		audioOptionsDict(NULL),
		videoOptionsDict(NULL),
		isOpenFile(0),
		isDecoding(false),
		videoDecodeEeventHandler(0)
{
	av_register_all();
	videoDecodeThread = new ASVideoDecodeThread();
}

ASNativePlayer::~ASNativePlayer() {

	if (pVideoCodecCtx != NULL) {
		avcodec_close(pVideoCodecCtx);
		pVideoCodecCtx = NULL;
	}

	if (pAudioCodecCtx != NULL) {
		avcodec_close(pAudioCodecCtx);
		pAudioCodecCtx = NULL;
	}

	if (pFormatCtx != NULL) {
		avformat_close_input(&pFormatCtx);
	}
	isOpenFile = 0;
	isDecoding = false;
	videoDecodeEeventHandler = 0;

	if(videoDecodeThread!=0){
		delete videoDecodeThread;
	}
}

int ASNativePlayer::ASOpenFile(char* filename) {
	if(access(filename,0) == -1) return -1;

	fileName = filename;
	// open the video file
	if(avformat_open_input(&pFormatCtx,filename,NULL,NULL) != 0){
		isOpenFile = 1;
		return -1; // Could't open file
	}


	// Retrive stream information
	if (avformat_find_stream_info(pFormatCtx, NULL) < 0) {
		return -1; // Couldn't find stream information
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
			continue;
		}
		if (pFormatCtx->streams[i]->codec->codec_type == AVMEDIA_TYPE_AUDIO) {
			audioStream = i;
			continue;
		}
	}
	return (audioStream != -1 && videoStream != -1);
}

int ASNativePlayer::ASOpenCodec() {
	int rect = -1;
	int bsupportVideo = -1;
	int bsupportAudio = -1;

	if(pFormatCtx==NULL) return -1;

	if (videoStream != -1) {
		pVideoCodecCtx = pFormatCtx->streams[videoStream]->codec;
	} else {
		LOGW("%s: %s\n", __func__, "videoStream == -1");
		bsupportVideo = -1;
	}

	if (audioStream != -1) {
		pAudioCodecCtx = pFormatCtx->streams[audioStream]->codec;
	}else {
#ifndef __ANDROID__
		LOGW("%s: %s\n", __func__, "audioStream == -1");
#else
		printf("%s: %s\n", __func__, "audioStream == -1\n");
#endif
		bsupportAudio = -1;
	}

	// Find the decoder for the video/audio stream
	if (pVideoCodec == NULL) {
		pVideoCodec = avcodec_find_decoder(pVideoCodecCtx->codec_id);
		if (pVideoCodec == NULL) {
			LOGW("%s", "unsupported video codec!\n");
		}
	} else {
		LOGW("%s", "pVideoCodec is NULL\n");
	}

	if (pAudioCodec == NULL) {
		pAudioCodec = avcodec_find_decoder(pAudioCodecCtx->codec_id);
		if (pAudioCodec == NULL) {
			LOGW("%s", "unsupported audio codec!\n");
		}
	} else {
		LOGW("%s", "pAudioCodec is NULL\n");
	}

	if(pAudioCodecCtx != NULL && pAudioCodec != NULL)
	{
		if(avcodec_open2(pAudioCodecCtx,pAudioCodec,&audioOptionsDict) < 0){
			LOGW("%s,%s",__func__,"audio avcodec_open2 failed!\n");
		}
		bsupportAudio = 1;
	}
	if(pVideoCodecCtx != NULL && pVideoCodec!= NULL){
		if(avcodec_open2(pVideoCodecCtx,pVideoCodec,&videoOptionsDict) < 0){
			LOGW("%s,%s",__func__,"video avcodec_open2 failed!\n");
			bsupportVideo = -1;
		}
		bsupportVideo = 1;
	}
	return bsupportVideo<0 || bsupportAudio<0;
}


std::string ASNativePlayer::getMediaSimpleInfo() {
	std::string simpleInfo;
	std::string videoCodecName;
	std::string audioCodecName;
	char info[1024]={0};
	char durationInfo[512]={0};

	AVFormatContext* ic = pFormatCtx;
	if(ic!=NULL){
		simpleInfo.append("iformat:");
		simpleInfo.append(ic->iformat->name);
		simpleInfo.append("\n");

		if (ic->duration != AV_NOPTS_VALUE) {
				            int hours, mins, secs, us;
				            int64_t duration = ic->duration + 5000;
				            secs = duration / AV_TIME_BASE;
				            us = duration % AV_TIME_BASE;
				            mins = secs / 60;
				            secs %= 60;
				            hours = mins / 60;
				            mins %= 60;
				            sprintf(durationInfo, "%02d:%02d:%02d.%02d", hours, mins, secs,
				                   (100 * us) / AV_TIME_BASE);
				            simpleInfo.append(durationInfo);
				            simpleInfo.append("\n");
		}
		if(pVideoCodecCtx!=NULL){
			const AVCodecDescriptor *description = av_codec_get_codec_descriptor(pVideoCodecCtx);
			videoCodecName = description->long_name;
		}
		if(pAudioCodecCtx!=NULL){
			const AVCodecDescriptor *description = av_codec_get_codec_descriptor(pAudioCodecCtx);
			audioCodecName = description->long_name;
		}

		simpleInfo.append("videoCodecName:");
		simpleInfo.append(videoCodecName);
		simpleInfo.append("\n");
		simpleInfo.append("audioCodecName:");
		simpleInfo.append(audioCodecName);
	}
	return simpleInfo;
}

int ASNativePlayer::ASStartVideoDecode() {
	if(videoDecodeEeventHandler!=0){
		if(videoDecodeThread!=0){
			VideoDecodeParam *param = new VideoDecodeParam();
			param->videoStream =videoStream;
			param->isRunning = &isDecoding;
			param->pFormatCtx = pFormatCtx;
			param->pVideoCodec = pVideoCodec;
			param->pVideoCodecCtx = pVideoCodecCtx;
			param->pVideoDecodeFuncCB = this->videoDecodeEeventHandler;
			isDecoding = true;
			videoDecodeThread->startDecodeThread(param);

			videoDecodeEeventHandler->startVideoDecoding(true);
		}

	}
}

int ASNativePlayer::ASStopVideoDecode() {
	if(videoDecodeEeventHandler!=0){
		videoDecodeEeventHandler->stopVideoDecoding(true);
	}
}

void ASNativePlayer::setVideoDecodeEventHandler(ASVideoDecodeCB* handle) {
	if(handle != 0)
		videoDecodeEeventHandler = handle;
}
