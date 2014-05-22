package com.asnetwork.adapter;


import com.asnetwok.asplayer.R;

import android.app.PendingIntent;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.ImageView;
import android.widget.TextView;

import com.asnetwork.common.Constants;
import com.asnetwork.domain.ASMediaFile;
import com.asnetwork.swig.ASNativePlayer;
import com.asnetwork.view.*;

public class ASMediaFileAapter<T extends ASMediaFile> 
	extends ASGenericAdapter<T> implements  OnItemClickListener  {
	
	
	public ASMediaFileAapter(Context cxt,int mItemResourceId) {
		super(cxt,mItemResourceId);
	}

	@Override
	public View getViewImp(int position, View convertView, ViewGroup parent) {
		ViewHolder holder = null;
		if(convertView == null){
			holder = new ViewHolder();
			convertView = mInflater.inflate((int) mItemResourceId, null);
			TextView textView = (TextView)convertView.findViewById(R.id.textview_video_title);
			ImageView imageView = (ImageView)convertView.findViewById(R.id.imageview_video_thumb);
			holder.textView = textView;
			holder.imageView = imageView;
			
			convertView.setTag(holder);
		}else {
			holder = (ViewHolder) convertView.getTag();
		}
		holder.textView.setText(dataSource.get(position).getDISPLAY_NAME());
		return convertView;
	}

	
	
	
	public static final class ViewHolder{
		public TextView textView;
		public ImageView imageView;
	}

	@Override
	public void onItemClick(AdapterView<?> parent, View view, int position,
			long id) {
		// TODO Auto-generated method stub
		Intent intent = new Intent(cxt,ASPlayerVideoActivity.class);
		
		intent.putExtra(Constants.MEDIA_FILE_NAME,
				this.dataSource.get(position).getDATA());
		cxt.startActivity(intent);
		
		/*ASNativePlayer player = ASNativePlayer.getInstance();
		if(player.getIsOpenFile()>0){
			player.releaseInstance();
		}
		player.ASOpenFile(this.dataSource.get(position).getDATA());
		player.ASOpenCodec();
		String description = player.getMediaSimpleInfo();
		
		intent.putExtra(Constants.MEDIA_FILE_NAME,description);
		cxt.startActivity(intent);*/
		
		/*ASNativePlayer player = ASNativePlayer.createNewInstance();
		ASVideoDecodeRecv decodeRecv = new ASVideoDecodeRecv();
		player.setVideoDecodeListern(decodeRecv);
		player.ASOpenFile(this.dataSource.get(position).getDATA());
		player.ASOpenCodec();
		player.ASStartVideoDecode();
		*/
//		player.ASStopVideoDecode();
//		ASNativePlayer.releaseInstance(player);
		
	}
	
}
