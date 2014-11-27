package com.asnetwork.view;

import java.util.List;

import com.asnetwok.asplayer.R;
import com.asnetwork.adapter.ASMediaFileAapter;
import com.asnetwork.domain.ASMediaFile;

import android.support.v4.app.Fragment;
import android.support.v4.app.FragmentActivity;
import android.app.Activity;
import android.os.Bundle;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ListView;

public class ASPlayerActivity extends FragmentActivity {

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_asplayer);

		if (savedInstanceState == null) {
			getSupportFragmentManager().beginTransaction().
				add(R.id.container, new PlaceholderFragment()).commit();
		}
		
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {

		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.asplayer, menu);
		return true;
	}

	@Override
	public boolean onOptionsItemSelected(MenuItem item) {
		// Handle action bar item clicks here. The action bar will
		// automatically handle clicks on the Home/Up button, so long
		// as you specify a parent activity in AndroidManifest.xml.
		int id = item.getItemId();
		if (id == R.id.action_settings) {
			return true;
		}
		return super.onOptionsItemSelected(item);
	}

	/**
	 * A placeholder fragment containing a simple view.
	 */
	public static class PlaceholderFragment extends Fragment {

		private ListView fileListView;
		
		public PlaceholderFragment() {
		}

		public View onCreateView(LayoutInflater inflater, ViewGroup container,
				Bundle savedInstanceState) {
			View rootView = inflater.inflate(R.layout.fragment_asplayer,
					container, false);
			fileListView = (ListView)rootView.findViewById(R.id.listview_media_list);
			setListView();
			return rootView;
		}
		
		public void setListView(){
			MediaFileFinder fileFinder = new MediaFileFinder(getActivity());
			List<ASMediaFile> resultFiles = fileFinder.getMediaFile(MediaFileFinder.MEDIA_VIDEO_TYPE);
			ASMediaFileAapter<ASMediaFile> fileAdapter = new 
						ASMediaFileAapter<ASMediaFile>(getActivity(),R.layout.media_list_item_layout);
			fileAdapter.dataSource = resultFiles;
			fileListView.setAdapter(fileAdapter);
			fileListView.setOnItemClickListener(fileAdapter);
		}
		
	}

	static {
		System.loadLibrary("avutil-52");
        System.loadLibrary("avcodec-55");
        System.loadLibrary("avformat-55");
        System.loadLibrary("swscale-2");
		System.loadLibrary("ASPlayer");
	}
}
