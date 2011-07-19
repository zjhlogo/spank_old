package com.zjhlogo.spank;

public class SpankLibrary
{
    static
    {
        System.loadLibrary("spank");
    }

    public static native void initialize(int width, int height);
    public static native void step();
}
