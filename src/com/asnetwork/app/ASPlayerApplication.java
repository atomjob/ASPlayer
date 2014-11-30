package com.asnetwork.app;

import com.asnetwork.service.ASMediaService;
import com.asnetwork.service.IASMediaPlayer;

import android.app.Application;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.IBinder;
import android.util.Log;

public class ASPlayerApplication extends Application {
	
	private static final String TAG = "ASPlayerApplication";
	public IASMediaPlayer mIASMediaPlayer = null;
	
	public ASPlayerApplication() {
		// TODO Auto-generated constructor stub
	}
	
	@Override
	public void onCreate() {
		// TODO Auto-generated method stub
		super.onCreate();
		Intent serviceIntent = new Intent(getApplicationContext(),ASMediaService.class);
		bindService(serviceIntent, mConnection, BIND_AUTO_CREATE);
	}
	
	
	private  ServiceConnection mConnection = new ServiceConnection() {
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
	
	
}
