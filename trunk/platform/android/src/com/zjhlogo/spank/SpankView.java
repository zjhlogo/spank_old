package com.zjhlogo.spank;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;

class SpankView extends GLSurfaceView
{
	public SpankView(Context context)
	{
		super(context);
		
		//setup context factory
        setEGLContextFactory(new SpankContextFactory());

        // set config chooser
        getHolder().setFormat(PixelFormat.TRANSLUCENT);
        setEGLConfigChooser(new SpankConfigChooser());

		// set renderer
		setRenderer(new SpankRenderer());
	}
}
