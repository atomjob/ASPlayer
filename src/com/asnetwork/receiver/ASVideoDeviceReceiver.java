package com.asnetwork.receiver;

import com.asnetwork.swig.ASMediaFileSourceEvent;
import com.asnetwork.swig.ASNativePlayer;
import com.asnetwork.swig.ASVideoInputEvent;
import com.asnetwork.swig.VideoInputParam;

public class ASVideoDeviceReceiver extends ASVideoInputEvent{
	
	@Override
	public void videoOpened(VideoInputParam para){
		
	}
	
	@Override
	public void videoStarted(VideoInputParam para){
		
	}
	
	@Override
	public void videoStopped(VideoInputParam para){
		
	}
	
	@Override
	public void videoClosed(VideoInputParam para){
//		ASNativePlayer.releaseInstance(para.)
	}
}
