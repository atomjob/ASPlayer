package com.asnetwork.view;

import com.asnetwok.asplayer.R;
import com.asnetwork.app.ASPlayerApplication;
import com.asnetwork.common.Constants;
import com.asnetwork.player.NativePlayer;
import com.asnetwork.service.ASMediaService;
import com.asnetwork.service.IASMediaPlayer;
//import com.asnetwork.receiver.ASVideoDeviceReceiver;
//import com.asnetwork.receiver.ASVideoDecodeRecv;
import com.asnetwork.swig.ASNativePlayer;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.IBinder;
import android.os.RemoteException;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class ASPlayerVideoActivity extends Activity implements SurfaceHolder.Callback{
	public final static String TAG = "ASPlayerVideoActivity";
	private SurfaceView videoSurfaceView;
	
//	IASMediaPlayer mIASMediaPlayer;
//	private NativePlayer player = null;
//	public static ASVideoDecodeRecv decodeStateRecv = new ASVideoDecodeRecv();
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_video);
		// set fullscreen style for this activity.Android4.4 test
		int mUIFlag = View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                | View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                | View.SYSTEM_UI_FLAG_LAYOUT_STABLE
                | View.SYSTEM_UI_FLAG_LOW_PROFILE
                | View.SYSTEM_UI_FLAG_FULLSCREEN
                | View.SYSTEM_UI_FLAG_HIDE_NAVIGATION;

		getWindow().getDecorView().setSystemUiVisibility(mUIFlag);
		
		videoSurfaceView = (SurfaceView)findViewById(R.id.surfaceView_video);
		videoSurfaceView.getHolder().addCallback(this);
		
//		boolean isOK = bindService(new Intent(this,ASMediaService.class), mConnection, BIND_AUTO_CREATE);
//		
//		if(!isOK){
//			Log.d(TAG, "bindService ASMediaService failed ");
//		}
	}

	 
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		
	}
	
	
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
//		player.play();
//		player.setDisplayHandle(holder.getSurface());
		String mediaFileName = 
				(String) this.getIntent().getExtras().
						get(Constants.MEDIA_FILE_NAME);
	  IASMediaPlayer mIASMediaPlayer = 	((ASPlayerApplication)getApplication()).mIASMediaPlayer;
		if(mIASMediaPlayer!=null){
			try {
				mIASMediaPlayer.playVideo(mediaFileName);
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
//		splayer.setDisplayHandle(holder.getSurface());
		
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		IASMediaPlayer mIASMediaPlayer = 	((ASPlayerApplication)getApplication()).mIASMediaPlayer;
		if(mIASMediaPlayer!=null){
			try {
				mIASMediaPlayer.stopVideo();
			} catch (RemoteException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
	/*
	private ServiceConnection mConnection = new ServiceConnection() {
	    // Called when the connection with the service is established
	    public void onServiceConnected(ComponentName className, IBinder service) {
	        // Following the example above for an AIDL interface,
	        // this gets an instance of the IRemoteInterface, which we can use to call on the service
	    	mIASMediaPlayer = IASMediaPlayer.Stub.asInterface(service);
	    }

	    // Called when the connection with the service disconnects unexpectedly
	    public void onServiceDisconnected(ComponentName className) {
	        Log.e(TAG, "Service has unexpectedly disconnected");
	        mIASMediaPlayer = null;
	    }
	};
	*/
}
