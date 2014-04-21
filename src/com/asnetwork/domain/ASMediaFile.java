package com.asnetwork.domain;

public class ASMediaFile {
		public int _ID;
	    public String DISPLAY_NAME;
	    public String DATA;
		public int get_ID() {
			return _ID;
		}
		public void set_ID(int _ID) {
			this._ID = _ID;
		}
		public String getDISPLAY_NAME() {
			return DISPLAY_NAME;
		}
		public void setDISPLAY_NAME(String dISPLAY_NAME) {
			DISPLAY_NAME = dISPLAY_NAME;
		}
		public String getDATA() {
			return DATA;
		}
		public void setDATA(String dATA) {
			DATA = dATA;
		}
		public ASMediaFile(int _ID, String dISPLAY_NAME, String dATA) {
			this._ID = _ID;
			DISPLAY_NAME = dISPLAY_NAME;
			DATA = dATA;
		}
	    
		public String toString(){
			return "_ID:"+_ID+" DISPLAY_NAME:"+DISPLAY_NAME+" DATA"+DATA;
		}
}