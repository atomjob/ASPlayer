package com.asnetwork.player;

import com.asnetwork.swig.ASNativePlayer;
import com.asnetwork.swig.VideoInputParam;

public class NativePlayer extends ASNativePlayer {
	
	
	private static NativePlayer instance = null;
	
	public static NativePlayer getInstance(){
		if(instance == null) instance = new NativePlayer();
		return instance;
	}
	
	public static void destoryInstance(){
		if(instance!=null)
			instance.releaseInstance();
		instance = null;
	}
	
	public NativePlayer(){
		super();
	}
	
	public void videoOpened(VideoInputParam para) {
		// AS_Native_PlayerJNI.ASNativePlayer_videoOpened(swigCPtr, this,
		// VideoInputParam.getCPtr(para), para);
		super.videoOpened(para);
	}

	public void videoStarted(VideoInputParam para) {
		// AS_Native_PlayerJNI.ASNativePlayer_videoStarted(swigCPtr, this,
		// VideoInputParam.getCPtr(para), para);
		super.videoStarted(para);
	}

	public void videoStopped(VideoInputParam para) {
		// AS_Native_PlayerJNI.ASNativePlayer_videoStopped(swigCPtr, this,
		// VideoInputParam.getCPtr(para), para);
		super.videoStopped(para);
	}

	public void videoClosed(VideoInputParam para) {
		// AS_Native_PlayerJNI.ASNativePlayer_videoClosed(swigCPtr, this,
		// VideoInputParam.getCPtr(para), para);
		super.videoClosed(para);
	}

}
