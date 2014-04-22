package com.asnetwork.receiver;

import com.asnetwork.swig.ASVideoDecodeEvent;

public class ASVideoDecodeRecv extends ASVideoDecodeEvent {
	public ASVideoDecodeRecv(){
		
	}
	@Override
	public int startVideoDecoding(boolean isStart){
		return 0;
	}
	
	@Override
	public int stopVideoDecoding(boolean isStop){
		return 0;
	}
}
