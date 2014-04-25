package com.asnetwork.receiver;

import android.util.Log;

import com.asnetwork.swig.ASNativePlayer;
import com.asnetwork.swig.ASVideoDecodeEvent;

public class ASVideoDecodeRecv extends ASVideoDecodeEvent {
	
	public ASNativePlayer player;
	
	public ASVideoDecodeRecv(ASNativePlayer player){
		this.player = player;
	}
	
	public ASVideoDecodeRecv(){
		
	}
	
	public void setPlayer(ASNativePlayer player){
		this.player = player;
	}
	@Override
	public int startVideoDecoding(boolean isStart){
		return 0;
	}
	
	@Override
	public int stopVideoDecoding(boolean isStop){
		Log.i("ASVideoDecodeRecv", "receive stopVideoDecoding event");
		if(isStop && player!=null){
			Log.i("ASVideoDecodeRecv", "before ASNativePlayer.releaseInstance");
			ASNativePlayer.releaseInstance(player);
			Log.i("ASVideoDecodeRecv", "after ASNativePlayer.releaseInstance");
		}
		return 0;
	}
}
