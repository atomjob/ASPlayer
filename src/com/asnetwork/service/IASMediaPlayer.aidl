package com.asnetwork.service;


/** Example service interface */
interface IASMediaPlayer{

	 int getPid();
    
     int playVideo(String sfilename);

  	 int stopVideo();
}