package com.zjhlogo.spank;

import javax.microedition.khronos.egl.EGL10;
import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.egl.EGLDisplay;

import android.opengl.GLSurfaceView;

class SpankConfigChooser implements GLSurfaceView.EGLConfigChooser
{
	/*
	 * This EGL config specification is used to specify 2.0 rendering. We use a
	 * minimum size of 4 bits for red/green/blue, but will perform actual
	 * matching in chooseConfig() below.
	 */
	private static int EGL_OPENGL_ES2_BIT = 4;
	private static int BLUE_BITS = 8;
	private static int GREEN_BITS = 8;
	private static int RED_BITS = 8;
	private static int ALPHA_BITS = 8;
	private static int DEPTH_BITS = 24;
	private static int STENCIL_BITS = 8;
	
	private static int[] s_configAttribs2 =
	{
		EGL10.EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL10.EGL_BLUE_SIZE, BLUE_BITS,
		EGL10.EGL_GREEN_SIZE, GREEN_BITS,
		EGL10.EGL_RED_SIZE, RED_BITS,
		EGL10.EGL_ALPHA_SIZE, ALPHA_BITS,
		EGL10.EGL_DEPTH_SIZE, DEPTH_BITS,
		EGL10.EGL_STENCIL_SIZE, STENCIL_BITS,
		EGL10.EGL_NONE
	};

	public EGLConfig chooseConfig(EGL10 egl, EGLDisplay display)
	{
		/*
		 * Get the number of minimally matching EGL configurations
		 */
		int[] num_config = new int[1];
		egl.eglChooseConfig(display, s_configAttribs2, null, 0, num_config);

		int numConfigs = num_config[0];

		if (numConfigs <= 0)
		{
			throw new IllegalArgumentException("No configs match configSpec");
		}

		/*
		 * Allocate then read the array of minimally matching EGL configs
		 */
		EGLConfig[] configs = new EGLConfig[numConfigs];
		egl.eglChooseConfig(display, s_configAttribs2, configs, numConfigs, num_config);

		/*
		 * Now return the "best" one
		 */
		return chooseBestConfig(egl, display, configs);
	}

	private EGLConfig chooseBestConfig(EGL10 egl, EGLDisplay display, EGLConfig[] configs)
	{
		for (EGLConfig config : configs)
		{
			int depth = findConfigAttrib(egl, display, config, EGL10.EGL_DEPTH_SIZE, 0);
			int stencil = findConfigAttrib(egl, display, config, EGL10.EGL_STENCIL_SIZE, 0);

			// We need at least mDepthSize and mStencilSize bits
			if (depth < DEPTH_BITS || stencil < STENCIL_BITS) continue;

			// We want an *exact* match for red/green/blue/alpha
			int red = findConfigAttrib(egl, display, config, EGL10.EGL_RED_SIZE, 0);
			int green = findConfigAttrib(egl, display, config, EGL10.EGL_GREEN_SIZE, 0);
			int blue = findConfigAttrib(egl, display, config, EGL10.EGL_BLUE_SIZE, 0);
			int alpha = findConfigAttrib(egl, display, config, EGL10.EGL_ALPHA_SIZE, 0);

			if (red == RED_BITS && green == GREEN_BITS && blue == BLUE_BITS && alpha == ALPHA_BITS)
			{
				return config;
			}
		}
		return null;
	}

	private int findConfigAttrib(EGL10 egl, EGLDisplay display, EGLConfig config, int attribute, int defaultValue)
	{
		int[] value = new int[1];
		if (egl.eglGetConfigAttrib(display, config, attribute, value))
		{
			return value[0];
		}
		
		return defaultValue;
	}

}
