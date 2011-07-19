package com.zjhlogo.spank;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

class SpankRenderer implements GLSurfaceView.Renderer
{
	public void onDrawFrame(GL10 gl)
	{
		SpankLibrary.step();
	}

	public void onSurfaceChanged(GL10 gl, int width, int height)
	{
		SpankLibrary.initialize(width, height);
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		// nothing to do
	}
}