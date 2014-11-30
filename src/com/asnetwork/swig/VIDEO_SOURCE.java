/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (http://www.swig.org).
 * Version 2.0.9
 *
 * Do not make changes to this file unless you know what you are doing--modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */

package com.asnetwork.swig;

public final class VIDEO_SOURCE {
  public final static VIDEO_SOURCE SOURCE_FILE = new VIDEO_SOURCE("SOURCE_FILE");
  public final static VIDEO_SOURCE SOURCE_NETWORK = new VIDEO_SOURCE("SOURCE_NETWORK");

  public final int swigValue() {
    return swigValue;
  }

  public String toString() {
    return swigName;
  }

  public static VIDEO_SOURCE swigToEnum(int swigValue) {
    if (swigValue < swigValues.length && swigValue >= 0 && swigValues[swigValue].swigValue == swigValue)
      return swigValues[swigValue];
    for (int i = 0; i < swigValues.length; i++)
      if (swigValues[i].swigValue == swigValue)
        return swigValues[i];
    throw new IllegalArgumentException("No enum " + VIDEO_SOURCE.class + " with value " + swigValue);
  }

  private VIDEO_SOURCE(String swigName) {
    this.swigName = swigName;
    this.swigValue = swigNext++;
  }

  private VIDEO_SOURCE(String swigName, int swigValue) {
    this.swigName = swigName;
    this.swigValue = swigValue;
    swigNext = swigValue+1;
  }

  private VIDEO_SOURCE(String swigName, VIDEO_SOURCE swigEnum) {
    this.swigName = swigName;
    this.swigValue = swigEnum.swigValue;
    swigNext = this.swigValue+1;
  }

  private static VIDEO_SOURCE[] swigValues = { SOURCE_FILE, SOURCE_NETWORK };
  private static int swigNext = 0;
  private final int swigValue;
  private final String swigName;
}
