package com.zjhlogo.spank;

public class SpankLibrary
{
    static
    {
        System.loadLibrary("android_test");
    }

    public static native void setPackagePath(String zipFilePath);
    
    public static native boolean initialize(int width, int height);
    public static native void terminate();
    public static native void step();
    
    public static native void touchBegin(int index, float x, float y);
    public static native void touchMove(int index, float x, float y);
    public static native void touchEnd(int index, float x, float y);
}
