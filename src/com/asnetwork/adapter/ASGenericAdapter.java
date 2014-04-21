package com.asnetwork.adapter;

import java.util.List;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;

public abstract class ASGenericAdapter<T> extends BaseAdapter {
	
	public List<T> dataSource;
	public Context cxt;
	public LayoutInflater mInflater;
	public int mItemResourceId;
	
	public ASGenericAdapter(Context cxt,int mItemResourceId){
		this.cxt = cxt;
		mInflater = LayoutInflater.from(cxt);
		this.mItemResourceId = mItemResourceId;
	}
	
	public abstract View getViewImp(int position, 
				View convertView, ViewGroup parent);
	
	@Override
	public int getCount() {
		// TODO Auto-generated method stub
		return dataSource.size();
	}

	@Override
	public Object getItem(int position) {
		// TODO Auto-generated method stub
		return dataSource.get(position);
	}

	@Override
	public long getItemId(int position) {
		// TODO Auto-generated method stub
		return 0;
	}

	@Override
	public View getView(int position, View convertView, ViewGroup parent) {
		// TODO Auto-generated method stub
		View view = getViewImp(position,convertView,parent);
		return view;
	}
	
	


}
