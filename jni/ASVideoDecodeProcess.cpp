/*
 * ASVideoDecodeProcess.cpp
 *
 *  Created on: 2014-5-3
 *      Author: atomshuai
 */

#include "ASVideoDecodeProcess.h"
#include "ASVideoFrameMalloc.h"

ASVideoDecodeProcess::ASVideoDecodeProcess():
pVideoThread_d(NULL),pAudioThread_d(NULL),
bIsStopVideoDecode(false),bIsStopAudioDecode(false){
	videoState = new VideoState();
    pthread_mutex_init(&videoStopMutex,NULL);
    pthread_mutex_init(&audioStopMutex,NULL);

}

ASVideoDecodeProcess::~ASVideoDecodeProcess() {
    pthread_mutex_destroy(&videoStopMutex);
    pthread_mutex_destroy(&audioStopMutex);
    LOGI("ASVideoDecodeProcess::~ASVideoDecodeProcess==>");
}

void ASVideoDecodeProcess::videoDecodeFunc(void* para) {
	LOGI("==>ASVideoDecodeProcess::videoDecodeFunc\n");
	ASVideoDecodeProcess *process = (ASVideoDecodeProcess*)para;
	pVideoState videoState = process->videoState;

	int frameFinished;
    bool isRunning = true;
    double pts;
	AVFrame *pFrame = av_frame_alloc();
	for (;;) {
            AVPacket pkt1, *packet = &pkt1;
            if(videoState->bIsSourceStop)
                goto exit;
        
            if(videoState->videoq.get(packet, 0) != AS_OK){
            	//sleep(0.5);
            	LOGI("==>ASVideoDecodeProcess::videoDecodeFunc  (2)");
            	continue;
            }
            LOGI("==>ASVideoDecodeProcess::videoDecodeFunc  (3)");

            pts = 0;
        
            // Save global pts to be stored in pFrame in first call
            ASVideoFrameMalloc::global_video_pkt_pts = packet->pts;

            // Decode video frame
            int length = avcodec_decode_video2(videoState->video_st->codec, pFrame, &frameFinished, packet);
            if(packet->dts == AV_NOPTS_VALUE
               && pFrame->opaque  && *(uint64_t*)pFrame->opaque!= AV_NOPTS_VALUE){
                pts = *(uint64_t *)pFrame->opaque;
            }else if(packet->dts != AV_NOPTS_VALUE){
                pts = packet->dts;
            }else {
                pts = 0;
            }
            pts *= av_q2d(videoState->video_st->time_base);
        
			// Did we get a video frame?
			if (frameFinished) {
				LOGI("===> videoDecodeFunc get a video frame pts: %f === > display\n",pts);
                
            }else{
            	LOGI("==>ASVideoDecodeProcess::videoDecodeFunc  (4) \n");
            }
        
            if(packet != NULL)  av_free_packet(packet);
        
            pthread_mutex_lock(&process->videoStopMutex);
            if(process->bIsStopVideoDecode){
                isRunning = false;
            }
            pthread_mutex_unlock(&process->videoStopMutex);
            if(!isRunning) goto exit;
            LOGI("==>ASVideoDecodeProcess::videoDecodeFunc  (5) \n");
		}
    goto exit;
    exit:{
    	LOGI("== > videoDecodeFunc exit");
        if(pFrame) av_free(pFrame);
        videoState->videoq.cleanAll();
        pthread_cond_signal(&videoState->pVideoDecodeCond);
        LOGI("videoDecodeFunc exit== > ");
    }
		return ;
}

void ASVideoDecodeProcess::runThread() {
	printf("==>ASVideoDecodeProcess::runThread\n");
	pthread_create(&pVideoThread_d, NULL,
			(void *(*)(void *))ASVideoDecodeProcess::videoDecodeFunc, (void*)this);
}

void ASVideoDecodeProcess::setVideoState(pVideoState videoState) {
	this->videoState = videoState;
}

void ASVideoDecodeProcess::stopVideoThread(){
    pthread_mutex_lock(&videoStopMutex);
    bIsStopVideoDecode = true;
    pthread_mutex_unlock(&videoStopMutex);
}
void ASVideoDecodeProcess::stopAudioThread(){
    pthread_mutex_lock(&videoStopMutex);
    bIsStopAudioDecode = true;
    pthread_mutex_unlock(&videoStopMutex);
}

void ASVideoDecodeProcess::audioDecodeFunc(void* para) {
	ASVideoDecodeProcess *process = (ASVideoDecodeProcess*)para;
	pVideoState videoState = process->videoState;
	LOGI("==>ASVideoDecodeProcess::videoDecodeFunc\n");
}

double ASVideoDecodeProcess::synchronizeVideo(VideoState *is,
                                              AVFrame *src_frame, double pts){
    double frame_delay;
    if(pts != 0){
        /* if we have pts, set video clock to it */
        is->video_clock = pts;
    }else{
        /* if we aren't given a pts, set it to the clock */
        pts = is->video_clock;
    }
    /* update the video clock */
    frame_delay = av_q2d(is->video_st->codec->time_base);
    /* if we are repeating a frame, adjust clock accordingly */
    //repeat_pict / (2*fps)
    frame_delay += src_frame->repeat_pict * (frame_delay * 0.5);
    is->video_clock += frame_delay;
    return pts;
}


void ASVideoDecodeProcess::videoRefreshTimer(void *userdata){
    VideoState *is = (VideoState *)userdata;
    VideoPicture *vp;
    double actual_delay, delay, sync_threhold, ref_clock, diff;
    if(is->video_st){
        if(is->pictq_size == 0){
//            schedule_refresh(is, 1);
        }else{
            vp = &is->pictq[is->pictq_rindex];

            delay = vp->pts - is->frame_last_pts; // the pts from last time
            if(delay <= 0 || delay >= 1.0){
                // if incorrect delay ,use previous one
                delay = is->frame_last_delay;
            }
            // save for next time
            is->frame_last_delay = delay;
            is->frame_last_pts = vp->pts;

            // updata delay to sync to audio
            ref_clock = ASVideoDecodeProcess::getAudioClock(is);
            diff = vp->pts - ref_clock;

            /*
             *   Skip or repeat the frame. Take delay into accout
             *   FFplay still doesn't konw if this is the best guess
             */
            sync_threhold = (delay > AV_SYNC_THRESHOLD) ? delay : AV_SYNC_THRESHOLD;
            if(fabs(diff) < AV_SYNC_THRESHOLD){
                if(diff <= -sync_threhold){
                    delay = 0;
                }else if(diff >= sync_threhold){
                    delay = 2 * delay;
                }
            }
            is->frame_timer += delay;

            // computer the real delay
            actual_delay = is->frame_timer - (av_gettime() / 1000000.0);
            if(actual_delay < 00.10){
                /* Really it should skip the picture instead */
				actual_delay = 0.010;
            }
//            schedule_refresh(is, (int) (actual_delay * 1000 + 0.5));
            /* show the picture! */
//			video_display(is);
            
            /* update queue for next picture! */
			if (++is->pictq_rindex == VIDEO_PICTURE_QUEUE_SIZE) {
				is->pictq_rindex = 0;
			}
            pthread_mutex_lock(&is->pictq_mutex);
//			SDL_LockMutex(is->pictq_mutex);
			is->pictq_size--;
//			SDL_CondSignal(is->pictq_cond);
            pthread_mutex_unlock(&is->pictq_mutex);
        }
    }
}

double ASVideoDecodeProcess::getAudioClock(VideoState *is){
    double pts;
	int hw_buf_size, bytes_per_sec, n;
    
	pts = is->audio_clock; /* maintained in the audio thread */
	hw_buf_size = is->audio_buf_size - is->audio_buf_index;
	bytes_per_sec = 0;
	n = is->audio_st->codec->channels * 2;
	if (is->audio_st) {
		bytes_per_sec = is->audio_st->codec->sample_rate * n;
	}
	if (bytes_per_sec) {
		pts -= (double) hw_buf_size / bytes_per_sec;
	}
	return pts;
}

int ASVideoDecodeProcess::queuePicture(VideoState *is){
    VideoPicture *vp;
	AVPicture pict;
    
    // windex is set to 0 initially
	vp = &is->pictq[is->pictq_windex];
    if(is->quit) return AS_FAILE;
    
    // windex in set 0 initial
    vp = &is->pictq[is->pictq_windex];
    
    return AS_OK;
}
