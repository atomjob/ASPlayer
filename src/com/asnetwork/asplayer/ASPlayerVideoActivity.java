package com.asnetwork.asplayer;

import com.asnetwok.asplayer.R;
import com.asnetwork.common.Constants;
import com.asnetwork.receiver.ASVideoDecodeRecv;
import com.asnetwork.swig.ASNativePlayer;

import android.app.Activity;
import android.os.Bundle;
import android.util.Log;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;

public class ASPlayerVideoActivity extends Activity implements SurfaceHolder.Callback{
	public final static String TAG = "ASPlayerVideoActivity";
	private SurfaceView videoSurfaceView;
	private ASNativePlayer player = null;
	public static ASVideoDecodeRecv decodeStateRecv = new ASVideoDecodeRecv();
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
	}

	public void initNativePlayer(){
		if(player == null){
			String mediaFileName = 
					(String) this.getIntent().getExtras().
							get(Constants.MEDIA_FILE_NAME);
			
			player = ASNativePlayer.createNewInstance();
			decodeStateRecv.setPlayer(player);
			int rect = this.player.ASOpenFile(mediaFileName);
			if(rect < 0) {
				ASNativePlayer.releaseInstance(player);
				Log.e(TAG,"ASOpenFile failed!!!");
				return;
			}
			
			rect = this.player.ASOpenCodec();
			if(rect < 0){
				ASNativePlayer.releaseInstance(player);
				Log.e(TAG,"ASOpenCodec failed!!!");
				return;
			}else{
				String infoString = player.getMediaSimpleInfo();
				Log.i(TAG,infoString);
			}
			this.player.setVideoDecodeListern(decodeStateRecv);
			this.player.ASStartVideoDecode();
//			return player;
		}
	}
	 
	@Override
	protected void onPause() {
		// TODO Auto-generated method stub
		super.onPause();
		
	}
	
	
	
	@Override
	public void surfaceCreated(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		initNativePlayer();
//		player.setDisplayHandle(holder.getSurface());
	}

	@Override
	public void surfaceChanged(SurfaceHolder holder, int format, int width,
			int height) {
		// TODO Auto-generated method stub
		player.setDisplayHandle(holder.getSurface());
		
	}

	@Override
	public void surfaceDestroyed(SurfaceHolder holder) {
		// TODO Auto-generated method stub
		if(player!=null){
			player.setIsDecoding(false);
			//ASNativePlayer.releaseInstance(player);
			//player = null;
		}
	}
}
