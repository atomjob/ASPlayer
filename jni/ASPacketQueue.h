/*
 * ASPacketQueue.h
 *
 *  Created on: 2014-5-1
 *      Author: atomshuai
 */

#ifndef ASPACKETQUEUE_H_
#define ASPACKETQUEUE_H_

#include "ASCommon.h"

#define VIDEO_PICTURE_QUEUE_SIZE 1
#define AV_SYNC_THRESHOLD 0.01
#define AV_NOSYNC_THRESHOLD 10.0

typedef struct VideoPicture {
    const unsigned char* data;
    int size;
    int srcWidth, srcHeight;/* source height & width */
    int width, height;
    int allocated;
    double pts;
} VideoPicture;


class ASPacketQueue {
public:
	ASPacketQueue();
	~ASPacketQueue();
	int put(AVPacket *pkt);
	int get(AVPacket *pkt,int block);
    int cleanAll();
public:
	  AVPacketList *first_pkt, *last_pkt;
      int nb_packets;
	  int size;
	  int isQuit;
	  pthread_mutex_t mutex;
      pthread_cond_t cond;
};



typedef struct VideoState{
	  AVFormatContext *pFormatCtx;
	  int             videoStream, audioStream;
	  AVStream        *audio_st;
	  ASPacketQueue     audioq;
	  uint8_t         audio_buf[(MAX_AUDIO_FRAME_SIZE * 3) / 2];
	  unsigned int    audio_buf_size;
	  unsigned int    audio_buf_index;
	  AVFrame         audio_frame;
	  AVPacket        audio_pkt;
	  uint8_t         *audio_pkt_data;
	  int             audio_pkt_size;
	  AVStream        *video_st;
	  ASPacketQueue     videoq;
      bool            bIsSourceStop;
    
	  VideoPicture    pictq[VIDEO_PICTURE_QUEUE_SIZE];
	  int             pictq_size, pictq_rindex, pictq_windex;
	  pthread_mutex_t       pictq_mutex;
	  pthread_cond_t        pictq_cond;

//	  pthread_t      *parse_tid;
//	  pthread_t      *video_tid;

//	  char            filename[1024];
	  int             quit;
    
    // sync video parameters
    double          frame_timer;
    double          frame_last_pts;
    double          frame_last_delay;
    double          video_clock; ///<pts of last decoded frame / predicted pts of next decoded frame
	
    double          audio_clock;
    
    AVIOContext     *io_context;
    struct SwsContext *sws_ctx;
    
    pthread_cond_t pVideoDecodeCond;
    pthread_cond_t pAudioDecodeCond;
    
	  VideoState():
		  pFormatCtx(NULL),videoStream(-1), audioStream(-1),
		  audio_st(NULL),audioq(),audio_buf_size(0),audio_buf_index(0),
		  audio_pkt(),audio_pkt_data(NULL),audio_pkt_size(0),video_st(NULL),
		  videoq(),quit(0),io_context(NULL),sws_ctx(NULL),bIsSourceStop(false),
          frame_timer(0),frame_last_pts(0),frame_last_delay(0),video_clock(0),pictq_size(0),
          pictq_rindex(0),pictq_windex(0){

              pthread_cond_init(&pVideoDecodeCond, NULL);
              pthread_cond_init(&pAudioDecodeCond, NULL);
              pthread_cond_init(&pictq_cond, NULL);
              pthread_mutex_init(&pictq_mutex,NULL);
              
	  }
	  ~VideoState(){
          pthread_cond_destroy(&pVideoDecodeCond);
          pthread_cond_destroy(&pAudioDecodeCond);
        }
}*pVideoState;

#endif /* ASPACKETQUEUE_H_ */
