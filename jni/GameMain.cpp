/*!
 * \file GameMain.cpp
 * \date 17-05-2011 21:09:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameMain.h"
#include "Main.h"
#include "MessageMgr.h"

#include "msg/MsgID.h"
#include "msg/MsgReader.h"

#include <android/native_activity.h>
#include <android/native_window.h>

static const char g_szVertexShader[] = 
    "attribute vec4 vPosition;\n"
    "void main() {\n"
    "  gl_Position = vPosition;\n"
    "}\n";

static const char g_szFragmentShader[] = 
    "precision mediump float;\n"
    "void main() {\n"
    "  gl_FragColor = vec4(0.0, 1.0, 0.0, 1.0);\n"
    "}\n";

GameMain::GameMain()
{
	m_bShutdown = false;
	m_eglDisplay = EGL_NO_DISPLAY;
	m_eglSurface = EGL_NO_SURFACE;
	m_eglContext = EGL_NO_CONTEXT;
	m_pInputQueue = NULL;
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;

	m_glVertexShader = 0;
	m_glFragmentShader = 0;
	m_glProgramObject = 0;
	m_glPositionHandler = 0;

	m_bRendererInitialized = false;

	RegisterMessage(MI_AAM_CREATE, (MSG_FUNC)&GameMain::OnActivityCreated);
	RegisterMessage(MI_AAM_DESTROY, (MSG_FUNC)&GameMain::OnActivityDestroy);
	RegisterMessage(MI_AAM_START, (MSG_FUNC)&GameMain::OnActivityStart);
	RegisterMessage(MI_AAM_RESUME, (MSG_FUNC)&GameMain::OnActivityResume);
	RegisterMessage(MI_AAM_SAVE_INSTANCE_STATE, (MSG_FUNC)&GameMain::OnActivitySaveInstanceState);
	RegisterMessage(MI_AAM_PAUSE, (MSG_FUNC)&GameMain::OnActivityPause);
	RegisterMessage(MI_AAM_STOP, (MSG_FUNC)&GameMain::OnActivityStop);
	RegisterMessage(MI_AAM_CONFIGURATION_CHANGED, (MSG_FUNC)&GameMain::OnActivityConfigurationChanged);
	RegisterMessage(MI_AAM_LOW_MEMORY, (MSG_FUNC)&GameMain::OnActivityLowMemory);
	RegisterMessage(MI_AAM_WINDOW_FOCUS_CHANGED, (MSG_FUNC)&GameMain::OnWindowFocusChanged);
	RegisterMessage(MI_AAM_NATIVE_WINDOW_CREATED, (MSG_FUNC)&GameMain::OnNativeWindowCreated);
	RegisterMessage(MI_AAM_NATIVE_WINDOW_DESTROYED, (MSG_FUNC)&GameMain::OnNativeWindowDestroy);
	RegisterMessage(MI_AAM_INPUT_QUEUE_CREATED, (MSG_FUNC)&GameMain::OnInputQueueCreated);
	RegisterMessage(MI_AAM_INPUT_QUEUE_DESTROYED, (MSG_FUNC)&GameMain::OnInputQueueDestroy);
}

GameMain::~GameMain()
{

}

void GameMain::Run()
{
	while (!m_bShutdown)
	{
		// get all the messages
		MessageMgr::GetInstance().DispatchMessage();

		// dispatch input events
		DispatchInputEvents();

		// update game
		Update(0.0f);

		// render game
		if (m_bRendererInitialized) Render();
	}
}

void GameMain::Update(float dt)
{
	// TODO: 
}

void GameMain::Render()
{
	static const GLfloat s_vVertices[] = { 0.0f, 0.5f, -0.5f, -0.5f, 0.5f, -0.5f };

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glUseProgram(m_glProgramObject);

	glVertexAttribPointer(m_glPositionHandler, 2, GL_FLOAT, GL_FALSE, 0, s_vVertices);
	glEnableVertexAttribArray(m_glPositionHandler);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	glFlush();
	eglSwapBuffers(m_eglDisplay, m_eglSurface);
}

bool GameMain::OnActivityCreated(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityCreated: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityDestroy(int nMsgID, StreamReader* pReader)
{
	m_bShutdown = true;

	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityDestroy: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityStart(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityStart: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityResume(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityResume: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivitySaveInstanceState(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivitySaveInstanceState: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityPause(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityPause: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityStop(int nMsgID, StreamReader* pReader)
{
	m_bShutdown = true;

	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityStop: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityConfigurationChanged(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityConfigurationChanged: %p\n", pActivity);
	return true;
}

bool GameMain::OnActivityLowMemory(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);

	LOGI("GameMain::OnActivityLowMemory: %p\n", pActivity);
	return true;
}

bool GameMain::OnWindowFocusChanged(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);
	int focused = 0;
	msgReader.Read(focused);
	LOGI("GameMain::OnWindowFocusChanged: %p --- %d\n", pActivity, focused);
	return true;
}

bool GameMain::OnNativeWindowCreated(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	ANativeActivity* pActivity = NULL;
	msgReader.Read(pActivity);
	ANativeWindow* pWindow = NULL;
	msgReader.Read(pWindow);
	int nWidth = 0;
	int nHeight = 0;
	int nFormat = 0;
	msgReader.Read(nWidth);
	msgReader.Read(nHeight);
	msgReader.Read(nFormat);
	LOGI("GameMain::OnNativeWindowCreated: %p --- %p, %dx%d:%d\n", pActivity, pWindow, nWidth, nHeight, nFormat);

	if (!InitializeDevice(pWindow))
	{
		LOGE("InitializeDevice Failed");
		return false;
	}

	m_bRendererInitialized = InitializeOpenGL();
	if (!m_bRendererInitialized)
	{
		LOGE("InitializeOpenGL Failed");
		return false;
	}

	return true;
}

bool GameMain::OnNativeWindowDestroy(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	ANativeActivity* pActivity = NULL;
	msgReader.Read(pActivity);
	ANativeWindow* pWindow = NULL;
	msgReader.Read(pWindow);
	int nWidth = 0;
	int nHeight = 0;
	int nFormat = 0;
	msgReader.Read(nWidth);
	msgReader.Read(nHeight);
	msgReader.Read(nFormat);
	LOGI("GameMain::OnNativeWindowDestroy: %p --- %p, %dx%d:%d\n", pActivity, pWindow, nWidth, nHeight, nFormat);

	m_bRendererInitialized = false;
	//TerminateOpenGL();
	//TerminateDevice();
	return true;
}

bool GameMain::OnInputQueueCreated(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);
	AInputQueue* pQueues = NULL;
	msgReader.Read(pQueues);
	LOGI("GameMain::OnInputQueueCreated: %p --- %p\n", pActivity, pQueues);

	m_pInputQueue = pQueues;
	return true;
}

bool GameMain::OnInputQueueDestroy(int nMsgID, StreamReader* pReader)
{
	MsgReader msgReader(pReader);
	void* pActivity = NULL;
	msgReader.Read(pActivity);
	void* pQueues = NULL;
	msgReader.Read(pQueues);
	LOGI("GameMain::OnInputQueueDestroy: %p --- %p\n", pActivity, pQueues);
	return true;
}

bool GameMain::OnKeyEvent()
{
	return true;
}

bool GameMain::OnMotionEvent(float x, float y)
{
	return true;
}

bool GameMain::InitializeDevice(ANativeWindow* window)
{
	static const EGLint s_ConfigAttribs[] =
	{
		EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_BLUE_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_RED_SIZE, 8,
		EGL_DEPTH_SIZE, 24,
		EGL_STENCIL_SIZE, 8,
		EGL_NONE,
	};

	static const EGLint s_ContextAttribs[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	// get display
	EGLDisplay display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	if (display == EGL_NO_DISPLAY)
	{
		LOGE("eglGetDisplay Failed");
		return false;
	}

	// initialize EGL
	EGLint major, minor;
	if (!eglInitialize(display, &major, &minor))
	{
		LOGE("eglInitialize Failed");
		return false;
	}
	LOGI("EGL version %d %d", major, minor);

	// choose config
	EGLConfig config = NULL;
	EGLint numConfig = 0;
	if (!eglChooseConfig(display, s_ConfigAttribs, &config, 1, &numConfig))
	{
		LOGE("eglChooseConfig Failed");
		return false;
	}

	// get attribute of EGL_NATIVE_VISUAL_ID
	EGLint format = 0;
	if (!eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format))
	{
		LOGE("eglGetConfigAttrib Failed");
		return false;
	}

	// set buffers
	ANativeWindow_setBuffersGeometry(window, 0, 0, format);

	// create context
	EGLSurface surface = eglCreateWindowSurface(display, config, window, NULL);
	if (surface == EGL_NO_SURFACE)
	{
		LOGE("eglCreateWindowSurface failed");
		return false;
	}

	EGLContext context = eglCreateContext(display, config, EGL_NO_CONTEXT, s_ContextAttribs);
	if (context == EGL_NO_CONTEXT)
	{
		LOGE("eglCreateContext failed");
		return false;
	}

	if (eglMakeCurrent(display, surface, surface, context) == EGL_FALSE)
	{
		LOGI("eglMakeCurrent failed");
		return false;
	}

	// get surface width and height
	EGLint width = 0;
	EGLint height = 0;
	eglQuerySurface(display, surface, EGL_WIDTH, &width);
	eglQuerySurface(display, surface, EGL_HEIGHT, &height);
	LOGI("surface size: %dx%d", width, height);

	m_eglDisplay = display;
	m_eglSurface = surface;
	m_eglContext = context;
	m_nScreenWidth = width;
	m_nScreenHeight = height;

	return true;
}

void GameMain::TerminateDevice()
{
	if (m_eglDisplay != EGL_NO_DISPLAY)
	{
		eglMakeCurrent(m_eglDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);

		if (m_eglContext != EGL_NO_CONTEXT)
		{
			eglDestroyContext(m_eglDisplay, m_eglContext);
			m_eglContext = EGL_NO_CONTEXT;
		}

		if (m_eglSurface != EGL_NO_SURFACE)
		{
			eglDestroySurface(m_eglDisplay, m_eglSurface);
			m_eglDisplay = EGL_NO_SURFACE;
		}

		eglTerminate(m_eglDisplay);
		m_eglDisplay = EGL_NO_DISPLAY;
	}
}

void GameMain::DispatchInputEvents()
{
	if (!m_pInputQueue) return;

	while (AInputQueue_hasEvents(m_pInputQueue) >= 1)
	{
		AInputEvent* pInputEvent = NULL;
		AInputQueue_getEvent(m_pInputQueue, &pInputEvent);
		if (AInputQueue_preDispatchEvent(m_pInputQueue, pInputEvent)) continue;

		int nEventType = AInputEvent_getType(pInputEvent);
		switch (nEventType)
		{
		case AINPUT_EVENT_TYPE_KEY:
			{
				OnKeyEvent();
			}
			break;
		case AINPUT_EVENT_TYPE_MOTION:
			{
				float x = AMotionEvent_getX(pInputEvent, 0);
				float y = AMotionEvent_getY(pInputEvent, 0);
				OnMotionEvent(x, y);
			}
			break;
		}

		AInputQueue_finishEvent(m_pInputQueue, pInputEvent, 1);
	}
}

bool GameMain::InitializeOpenGL()
{
	TerminateOpenGL();

	m_glVertexShader = LoadShader(g_szVertexShader, GL_VERTEX_SHADER);
	if (!m_glVertexShader)
	{
		LOGE("Load Vertex Shader Failed");
		return false;
	}

	m_glFragmentShader = LoadShader(g_szFragmentShader, GL_FRAGMENT_SHADER);
	if (!m_glFragmentShader)
	{
		LOGE("Load Fragment Shader Failed");
		return false;
	}

	m_glProgramObject = glCreateProgram();
	if (!m_glProgramObject)
	{
		LOGE("Create Program Failed");
		return false;
	}

	glAttachShader(m_glProgramObject, m_glVertexShader);
	glAttachShader(m_glProgramObject, m_glFragmentShader);
	glLinkProgram(m_glProgramObject);

	GLint glLinked = 0;
	glGetProgramiv(m_glProgramObject, GL_LINK_STATUS, &glLinked);
	if (glLinked != GL_TRUE)
	{
		GLint nErrorLength = 0;
		glGetProgramiv(m_glProgramObject, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 1)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetProgramInfoLog(m_glProgramObject, nErrorLength, NULL, pszErrorLog);
			LOGI("Error linking program: %s\n", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteProgram(m_glProgramObject);
		return false;
	}

	m_glPositionHandler = glGetAttribLocation(m_glProgramObject, "vPosition");
	glViewport(0, 0, m_nScreenWidth, m_nScreenHeight);
	return true;
}

void GameMain::TerminateOpenGL()
{
	if (m_glProgramObject)
	{
		glDeleteProgram(m_glProgramObject);
		m_glProgramObject = 0;
	}

	if (m_glVertexShader)
	{
		glDeleteShader(m_glVertexShader);
		m_glVertexShader = 0;
	}

	if (m_glFragmentShader)
	{
		glDeleteShader(m_glFragmentShader);
		m_glFragmentShader = 0;
	}
}

GLuint GameMain::LoadShader(const char* pszShaderSource, GLenum eType)
{
	GLuint glShader = glCreateShader(eType);
	if (glShader == 0) return 0;

	glShaderSource(glShader, 1, &pszShaderSource, NULL);
	glCompileShader(glShader);

	// check the compile status
	GLint glCompiled = 0;
	glGetShaderiv(glShader, GL_COMPILE_STATUS, &glCompiled);
	if (glCompiled == 0)
	{
		GLint nErrorLength = 0;
		glGetShaderiv(glShader, GL_INFO_LOG_LENGTH, &nErrorLength);
		if (nErrorLength > 1)
		{
			char* pszErrorLog = new char[nErrorLength];
			glGetShaderInfoLog(glShader, nErrorLength, NULL, pszErrorLog);
			LOGI("Error compiling shader: %s\n", pszErrorLog);
			delete[] pszErrorLog;
		}

		glDeleteShader(glShader);
		return 0;
	}

	return glShader;
}
