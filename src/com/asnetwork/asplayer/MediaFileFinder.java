package com.asnetwork.asplayer;
import java.util.ArrayList;
import java.util.List;

import com.asnetwork.domain.ASMediaFile;

import android.content.ContentResolver;
import android.content.Context;
import android.database.Cursor;
import android.provider.MediaStore;
import android.util.Log;

public class MediaFileFinder {

	private String TAG = "MediaFileFinder";
	public Context ctx;
	
	public static final int MEDIA_VIDEO_TYPE = 0;
	public static final int MEDIA_AUDIO_TYPE = 1;
	
	public MediaFileFinder(Context ctx){
		this.ctx = ctx;
	}
	
	
	public List<ASMediaFile> getMediaFile(int MediaType){
		 
		 ContentResolver contentResolver = ctx.getContentResolver();
		 ArrayList<ASMediaFile>  resultFiles = new ArrayList<ASMediaFile>();
		 Cursor cursor =  null;
		 String projection[] = { 
					 MediaStore.Video.Media._ID,  
	                 MediaStore.Video.Media.DISPLAY_NAME,  
	                 MediaStore.Video.Media.DATA
                 };  
		 	if(MediaType == MEDIA_AUDIO_TYPE){
		 		cursor = contentResolver.query(MediaStore.Video.Media.EXTERNAL_CONTENT_URI, 
		 				projection,null, null, MediaStore.Audio.Media.DEFAULT_SORT_ORDER);
		 	}
		 	if(MediaType == MEDIA_VIDEO_TYPE){
		 		cursor = contentResolver.query(MediaStore.Video.Media.EXTERNAL_CONTENT_URI,
		 				projection, null, null, MediaStore.Video.Media.DEFAULT_SORT_ORDER);
		 	}
	        if(cursor!=null){
	        	cursor.moveToFirst();
		        for(int i = 0; i < cursor.getCount(); i++){
		        	int id = cursor.getInt(0);
		        	String displayName = cursor.getString(1);
		        	String data = cursor.getString(2);
		        	ASMediaFile mediaFile = new ASMediaFile(id,displayName,
		        			data);
		        	Log.i(TAG, mediaFile.toString());

		        	resultFiles.add(mediaFile);
		            cursor.moveToNext();
		        }
		        cursor.close();
		        return resultFiles;
	        }
	        return null;
		}
	    

}
