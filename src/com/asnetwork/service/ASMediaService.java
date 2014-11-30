package com.asnetwork.service;

import android.app.Service;
import android.content.Intent;
import android.os.Binder;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Looper;
import android.os.Message;
import android.os.RemoteException;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.widget.Toast;
import android.widget.ViewFlipper;

import com.asnetwork.player.NativePlayer;
import com.asnetwork.swig.ASNativePlayer;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ASMediaService extends Service {

    private  static final String TAG = "ASMediaService";
    private static NativePlayer nativePlayer = null;
    
    private static final ExecutorService executors = Executors.newCachedThreadPool(); 
    
    
    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {
        Toast.makeText(this, "service starting", Toast.LENGTH_SHORT).show();

        // For each start request, send a message to start a job and deliver the
        // start ID so we know which request we're stopping when we finish the job
        //Message msg = mServiceHandler.obtainMessage();
        //msg.arg1 = startId;
//        mServiceHandler.sendMessage(msg);

        // If we get killed, after returning from here, restart
        return START_STICKY;
    }

    @Override
    public IBinder onBind(Intent intent) {
        // We don't provide binding, so return null
        return mBinder;
    }

    @Override
    public void onDestroy() {
        Toast.makeText(this, "service done", Toast.LENGTH_SHORT).show();
    }

    
    
    private final IASMediaPlayer.Stub mBinder = new IASMediaPlayer.Stub() {

    	@Override
    	public int getPid() throws RemoteException {
    		// TODO Auto-generated method stub
    		return 0;
    	}
    	
		@Override
		public int playVideo(final String sfilename) throws RemoteException {
			// TODO Auto-generated method stub
			executors.execute(new Runnable() {
				
				@Override
				public void run() {
					// TODO Auto-generated method stub
					nativePlayer = NativePlayer.getInstance();
					nativePlayer.playVideo(sfilename);
				}
			});
			
			return 0;
		}

		@Override
		public int stopVideo() throws RemoteException {
			// TODO Auto-generated method stub
			executors.execute(new Runnable() {
				@Override
				public void run() {
					if(nativePlayer!=null){
						nativePlayer.stopVideo();
					}
				}
			});
			
			return 0;
		}
       
    };

    static {
		System.loadLibrary("avutil-52");
        System.loadLibrary("avcodec-55");
        System.loadLibrary("avformat-55");
        System.loadLibrary("swscale-2");
		System.loadLibrary("ASPlayer");
	}

}
