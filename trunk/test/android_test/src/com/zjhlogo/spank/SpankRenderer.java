package com.zjhlogo.spank;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;

import android.opengl.GLSurfaceView;

class SpankRenderer implements GLSurfaceView.Renderer
{
	public void onSurfaceChanged(GL10 gl, int width, int height)
	{
		if (!SpankLibrary.initialize(width, height))
		{
			// TODO: logout
		}
	}

	public void onSurfaceCreated(GL10 gl, EGLConfig config)
	{
		// nothing to do
	}
	
	public void onDrawFrame(GL10 gl)
	{
		SpankLibrary.step();
	}
}
