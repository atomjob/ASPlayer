/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.asnetwork.swig;

public class AS_Native_PlayerJNI {
  public final static native long new_ucArray(int jarg1);
  public final static native void delete_ucArray(long jarg1);
  public final static native short ucArray_getitem(long jarg1, ucArray jarg1_, int jarg2);
  public final static native void ucArray_setitem(long jarg1, ucArray jarg1_, int jarg2, short jarg3);
  public final static native long ucArray_cast(long jarg1, ucArray jarg1_);
  public final static native long ucArray_frompointer(long jarg1);
  public final static native void VideoInputParam_src_width_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_src_width_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_src_height_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_src_height_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_dest_width_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_dest_width_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_dest_height_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_dest_height_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_colorSpaceType_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_colorSpaceType_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_currentState_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_currentState_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_currentActionState_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_currentActionState_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_nextAction_set(long jarg1, VideoInputParam jarg1_, int jarg2);
  public final static native int VideoInputParam_nextAction_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_decodeProcess_set(long jarg1, VideoInputParam jarg1_, long jarg2);
  public final static native long VideoInputParam_decodeProcess_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_fileSource_set(long jarg1, VideoInputParam jarg1_, long jarg2);
  public final static native long VideoInputParam_fileSource_get(long jarg1, VideoInputParam jarg1_);
  public final static native void VideoInputParam_videoState_set(long jarg1, VideoInputParam jarg1_, long jarg2);
  public final static native long VideoInputParam_videoState_get(long jarg1, VideoInputParam jarg1_);
  public final static native long new_VideoInputParam();
  public final static native void delete_VideoInputParam(long jarg1);
  public final static native long new_ASVideoInputEvent();
  public final static native void delete_ASVideoInputEvent(long jarg1);
  public final static native void ASVideoInputEvent_videoOpened(long jarg1, ASVideoInputEvent jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASVideoInputEvent_videoStarted(long jarg1, ASVideoInputEvent jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASVideoInputEvent_videoStopped(long jarg1, ASVideoInputEvent jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASVideoInputEvent_videoClosed(long jarg1, ASVideoInputEvent jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASVideoInputEvent_director_connect(ASVideoInputEvent obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void ASVideoInputEvent_change_ownership(ASVideoInputEvent obj, long cptr, boolean take_or_release);
  public final static native long new_ASVideoInput();
  public final static native void delete_ASVideoInput(long jarg1);
  public final static native int ASVideoInput_videoOpen(long jarg1, ASVideoInput jarg1_, String jarg2, int jarg3);
  public final static native int ASVideoInput_videoStart(long jarg1, ASVideoInput jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native int ASVideoInput_videoStop(long jarg1, ASVideoInput jarg1_);
  public final static native int ASVideoInput_videoClose(long jarg1, ASVideoInput jarg1_);
  public final static native void ASVideoInput_setEventCB(long jarg1, ASVideoInput jarg1_, long jarg2, ASVideoInputEvent jarg2_);
  public final static native void ASVideoInput_pEventCB_set(long jarg1, ASVideoInput jarg1_, long jarg2, ASVideoInputEvent jarg2_);
  public final static native long ASVideoInput_pEventCB_get(long jarg1, ASVideoInput jarg1_);
  public final static native void ASVideoInput_innerParam_set(long jarg1, ASVideoInput jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native long ASVideoInput_innerParam_get(long jarg1, ASVideoInput jarg1_);
  public final static native void ASVideoInput_isStart_set(long jarg1, ASVideoInput jarg1_, boolean jarg2);
  public final static native boolean ASVideoInput_isStart_get(long jarg1, ASVideoInput jarg1_);
  public final static native void ASVideoInput_isOpen_set(long jarg1, ASVideoInput jarg1_, boolean jarg2);
  public final static native boolean ASVideoInput_isOpen_get(long jarg1, ASVideoInput jarg1_);
  public final static native void ASVideoInput_director_connect(ASVideoInput obj, long cptr, boolean mem_own, boolean weak_global);
  public final static native void ASVideoInput_change_ownership(ASVideoInput obj, long cptr, boolean take_or_release);
  public final static native long ASNativePlayer_createNewInstance();
  public final static native long ASNativePlayer_getInstance();
  public final static native void ASNativePlayer_releaseInstance__SWIG_0(long jarg1, ASNativePlayer jarg1_);
  public final static native void ASNativePlayer_releaseInstance__SWIG_1();
  public final static native void ASNativePlayer_g_instance_set(long jarg1, ASNativePlayer jarg1_);
  public final static native long ASNativePlayer_g_instance_get();
  public final static native long new_ASNativePlayer();
  public final static native void delete_ASNativePlayer(long jarg1);
  public final static native int ASNativePlayer_playVideo(long jarg1, ASNativePlayer jarg1_, String jarg2);
  public final static native int ASNativePlayer_stopVideo(long jarg1, ASNativePlayer jarg1_);
  public final static native void ASNativePlayer_videoOpened(long jarg1, ASNativePlayer jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASNativePlayer_videoStarted(long jarg1, ASNativePlayer jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASNativePlayer_videoStopped(long jarg1, ASNativePlayer jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASNativePlayer_videoClosed(long jarg1, ASNativePlayer jarg1_, long jarg2, VideoInputParam jarg2_);
  public final static native void ASNativePlayer_state_set(long jarg1, ASNativePlayer jarg1_, int jarg2);
  public final static native int ASNativePlayer_state_get(long jarg1, ASNativePlayer jarg1_);
  public final static native void ASNativePlayer_filename_set(long jarg1, ASNativePlayer jarg1_, String jarg2);
  public final static native String ASNativePlayer_filename_get(long jarg1, ASNativePlayer jarg1_);
  public final static native long ASNativePlayer_SWIGUpcast(long jarg1);

  public static void SwigDirector_ASVideoInputEvent_videoOpened(ASVideoInputEvent self, long para) {
    self.videoOpened((para == 0) ? null : new VideoInputParam(para, false));
  }
  public static void SwigDirector_ASVideoInputEvent_videoStarted(ASVideoInputEvent self, long para) {
    self.videoStarted((para == 0) ? null : new VideoInputParam(para, false));
  }
  public static void SwigDirector_ASVideoInputEvent_videoStopped(ASVideoInputEvent self, long para) {
    self.videoStopped((para == 0) ? null : new VideoInputParam(para, false));
  }
  public static void SwigDirector_ASVideoInputEvent_videoClosed(ASVideoInputEvent self, long para) {
    self.videoClosed((para == 0) ? null : new VideoInputParam(para, false));
  }
  public static int SwigDirector_ASVideoInput_videoOpen(ASVideoInput self, String url, int srcType) {
    return self.videoOpen(url, VIDEO_SOURCE.swigToEnum(srcType));
  }
  public static int SwigDirector_ASVideoInput_videoStart(ASVideoInput self, long para) {
    return self.videoStart((para == 0) ? null : new VideoInputParam(para, false));
  }
  public static int SwigDirector_ASVideoInput_videoStop(ASVideoInput self) {
    return self.videoStop();
  }
  public static int SwigDirector_ASVideoInput_videoClose(ASVideoInput self) {
    return self.videoClose();
  }

  private final static native void swig_module_init();
  static {
    swig_module_init();
  }
}
