package com.zjhlogo.spank;

import android.content.Context;
import android.graphics.PixelFormat;
import android.opengl.GLSurfaceView;
import android.view.MotionEvent;
import android.view.SurfaceHolder;

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

	@Override
	public void surfaceDestroyed(SurfaceHolder holder)
	{
		super.surfaceDestroyed(holder);
		SpankLibrary.terminate();
	}
	
	@Override
    public boolean onTouchEvent(MotionEvent event)
	{
		switch (event.getAction())
		{
		case MotionEvent.ACTION_DOWN:
			{
				SpankLibrary.touchBegin(0, event.getX(), event.getY());
			}
			break;
		case MotionEvent.ACTION_MOVE:
			{
				SpankLibrary.touchMove(0, event.getX(), event.getY());
			}
			break;
		case MotionEvent.ACTION_UP:
		case MotionEvent.ACTION_CANCEL:
			{
				SpankLibrary.touchEnd(0, event.getX(), event.getY());
			}
			break;
		}

		return true;
	}
}
