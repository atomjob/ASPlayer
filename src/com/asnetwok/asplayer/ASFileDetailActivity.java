package com.asnetwok.asplayer;

import com.asnetwork.common.Constrant;

import android.app.Activity;
import android.app.Fragment;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.TextView;

public class ASFileDetailActivity extends Activity {
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		// TODO Auto-generated method stub
		super.onCreate(savedInstanceState);
		this.setContentView(R.layout.activity_media_file_detail);
		TextView txView = (TextView)findViewById(R.id.textview_media_detail);
		String detailString = 
				(String) getIntent().getExtras().get(Constrant.MEDIA_FILE_NAME);
		txView.setText(detailString);
	}
	
	public static class PlaceholderFragment extends Fragment{
		@Override
		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			// TODO Auto-generated method stub
			super.onCreateView(inflater, container, savedInstanceState);
			View view = inflater.inflate(R.layout.activity_media_file_detail, null);
			TextView txView = (TextView)view.findViewById(R.id.textview_media_detail);
			String detailString = 
					(String) getActivity().getIntent().getExtras().get(Constrant.MEDIA_FILE_NAME);
			txView.setText(detailString);
			return view;
		}
	}
}


