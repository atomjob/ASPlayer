/*
 * ASPacketQueue.cpp
 *
 *  Created on: 2014-5-1
 *      Author: atomshuai
 */

#include "ASPacketQueue.h"

ASPacketQueue::ASPacketQueue():first_pkt(NULL),last_pkt(NULL) ,
nb_packets(0),size(0){
	pthread_mutex_init(&mutex,NULL);
    pthread_cond_init(&cond, NULL);
}

ASPacketQueue::~ASPacketQueue() {
	pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
}


int ASPacketQueue::put(AVPacket* pkt) {
    AVPacketList *pkt1;
	if (av_dup_packet(pkt) < 0) {
		return -1;
	}
	pkt1 = (AVPacketList *)av_malloc(sizeof(AVPacketList));
	if (!pkt1)
		return -1;
	//pkt1->pkt = *pkt;
    av_copy_packet(&pkt1->pkt , pkt);
//    av_free_packet(ptk);
	pkt1->next = NULL;
    
	pthread_mutex_lock(&mutex);
    
	if (!last_pkt)
		first_pkt = pkt1;
	else
		last_pkt->next = pkt1;
	last_pkt = pkt1;
	nb_packets++;
	size += pkt1->pkt.size;
    
    pthread_cond_signal(&cond);
	pthread_mutex_unlock(&mutex);
    return AS_OK;
}

int ASPacketQueue::get(AVPacket* pkt,int block) {
    AVPacketList *pkt1;
	int ret;
    
	pthread_mutex_lock(&mutex);
	for (;;) {
        
		if (isQuit) {
			ret = AS_FAILE;
			break;
		}
        
		pkt1 = first_pkt;
		if (pkt1) {
			first_pkt = pkt1->next;
			if (!first_pkt)
				last_pkt = NULL;
			nb_packets--;
			size -= pkt1->pkt.size;

            // NOTICE: deep copy packet data and avoid memory leak
            // *pkt = pkt1->pkt;
            av_copy_packet(pkt,&pkt1->pkt);
            av_free_packet(&pkt1->pkt);
            av_free(pkt1);
			ret = AS_OK;
			break;
		} else if (!block) {
			ret = AS_FAILE;
			break;
		} else {
            pthread_cond_wait(&cond,&mutex);
		}
	}
	pthread_mutex_unlock(&mutex);
	return ret;
}


int ASPacketQueue::cleanAll(){
    int ret;
    AVPacketList *curNode;
	pthread_mutex_lock(&mutex);
    
    do{
        curNode = first_pkt;
        if(curNode!=NULL)
            first_pkt = first_pkt->next;
        else{
        	pthread_mutex_unlock(&mutex);
        	return AS_OK;
        }

        av_free_packet(&curNode->pkt);
        nb_packets--;
        size -= curNode->pkt.size;
        free(curNode);
    }while(curNode!=NULL);
    
    ret = AS_OK;
	pthread_mutex_unlock(&mutex);
	return ret;

}
