/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.asnetwork.swig;

public class IVideoDecodeCB {
  private long swigCPtr;
  protected boolean swigCMemOwn;

  protected IVideoDecodeCB(long cPtr, boolean cMemoryOwn) {
    swigCMemOwn = cMemoryOwn;
    swigCPtr = cPtr;
  }

  protected static long getCPtr(IVideoDecodeCB obj) {
    return (obj == null) ? 0 : obj.swigCPtr;
  }

  protected void finalize() {
    delete();
  }

  public synchronized void delete() {
    if (swigCPtr != 0) {
      if (swigCMemOwn) {
        swigCMemOwn = false;
        AS_Native_PlayerJNI.delete_IVideoDecodeCB(swigCPtr);
      }
      swigCPtr = 0;
    }
  }

  protected void swigDirectorDisconnect() {
    swigCMemOwn = false;
    delete();
  }

  public void swigReleaseOwnership() {
    swigCMemOwn = false;
    AS_Native_PlayerJNI.IVideoDecodeCB_change_ownership(this, swigCPtr, false);
  }

  public void swigTakeOwnership() {
    swigCMemOwn = true;
    AS_Native_PlayerJNI.IVideoDecodeCB_change_ownership(this, swigCPtr, true);
  }

  public IVideoDecodeCB() {
    this(AS_Native_PlayerJNI.new_IVideoDecodeCB(), true);
    AS_Native_PlayerJNI.IVideoDecodeCB_director_connect(this, swigCPtr, swigCMemOwn, true);
  }

  public int startVideoDecoding(boolean isStart) {
    return AS_Native_PlayerJNI.IVideoDecodeCB_startVideoDecoding(swigCPtr, this, isStart);
  }

  public int stopVideoDecoding(boolean isStop) {
    return AS_Native_PlayerJNI.IVideoDecodeCB_stopVideoDecoding(swigCPtr, this, isStop);
  }

  public int recvDecodeData(String data, int width, int height) {
    return AS_Native_PlayerJNI.IVideoDecodeCB_recvDecodeData(swigCPtr, this, data, width, height);
  }

}
