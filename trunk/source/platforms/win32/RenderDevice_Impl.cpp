/*!
 * \file RenderDevice_Impl.cpp
 * \date 23-07-2011 10:33:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Impl.h"
#include <GLES2/gl2.h>
#include <IConfig.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Impl s_RenderDevice_Impl;
	return s_RenderDevice_Impl;
}

RenderDevice_Impl::RenderDevice_Impl()
{
	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;
	m_hWindow = NULL;
}

RenderDevice_Impl::~RenderDevice_Impl()
{
	// TODO:
}

bool RenderDevice_Impl::Initialize()
{
	if (!InitializeWindow()) return false;
	if (!InitializeEGL(m_hWindow)) return false;
	return true;
}

void RenderDevice_Impl::Terminate()
{
	TerminateEGL();
	TerminateWindow();
}

void RenderDevice_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// TODO: clear up render state
}

void RenderDevice_Impl::EndRender()
{
	eglSwapBuffers(m_EGLDisplay, m_EGLSurface);
}

bool RenderDevice_Impl::InitializeWindow()
{
	HINSTANCE hInstance = GetModuleHandle(NULL);

	WNDCLASS winClass;
	memset(&winClass, 0, sizeof(winClass));
	winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	winClass.lpfnWndProc = (WNDPROC)RenderDevice_Impl::MainWndProc;
	winClass.cbClsExtra = 0;
	winClass.cbWndExtra = 0;
	winClass.hInstance = hInstance;
	winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	winClass.hbrBackground = NULL;
	winClass.lpszMenuName = NULL;
	winClass.lpszClassName = IConfig::GetInstance().GetString("WINDOW_CLASS");
	RegisterClass(&winClass);

	// screen width, height
	int nScreenWidth = GetSystemMetrics(SM_CXSCREEN);
	int nScreenHeight = GetSystemMetrics(SM_CYSCREEN);

	// window width, height
	DWORD dwStyle = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	int winWidth = IConfig::GetInstance().GetInt("WINDOW_WIDTH");
	int winHeight = IConfig::GetInstance().GetInt("WINDOW_HEIGHT");
	RECT rc = {0, 0, winWidth, winHeight};
	AdjustWindowRect(&rc, dwStyle, FALSE);
	int nAdjustWidth = rc.right - rc.left;
	int nAdjustHeight = rc.bottom - rc.top;

	// create the window
	m_hWindow = CreateWindow(
		IConfig::GetInstance().GetString("WINDOW_CLASS"),
		IConfig::GetInstance().GetString("WINDOW_TITLE"),
		dwStyle,
		(nScreenWidth-nAdjustWidth)/2,
		(nScreenHeight-nAdjustHeight)/2,
		nAdjustWidth,
		nAdjustHeight,
		NULL, NULL, hInstance, NULL);

	ShowWindow(m_hWindow, SW_SHOW);
	SetForegroundWindow(m_hWindow);
	SetFocus(m_hWindow);

	return true;
}

void RenderDevice_Impl::TerminateWindow()
{
	if (m_hWindow)
	{
		DestroyWindow(m_hWindow);
		m_hWindow = NULL;
	}
}

LRESULT CALLBACK RenderDevice_Impl::MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
	{
	case WM_DESTROY:
		{
			PostQuitMessage(0);
		}
		break;
	default:
		{
			return DefWindowProc(hWnd, uMsg, wParam, lParam);
		}
		break;
	}

	return 0;
}

bool RenderDevice_Impl::InitializeEGL(HWND hWindow)
{
	static const EGLint s_EGLAttributes[] =
	{
		EGL_RED_SIZE, 8,
		EGL_GREEN_SIZE, 8,
		EGL_BLUE_SIZE, 8,
		EGL_DEPTH_SIZE, 16,
		EGL_RENDERABLE_TYPE, EGL_OPENGL_ES2_BIT,
		EGL_NONE
	};

	static const EGLint s_EGLContextAttributes[] =
	{
		EGL_CONTEXT_CLIENT_VERSION, 2,
		EGL_NONE
	};

	HDC hDisplay = GetDC(NULL);
	if (!hDisplay) return false;

	m_EGLDisplay = eglGetDisplay(hDisplay);
	eglInitialize(m_EGLDisplay, NULL, NULL);

	EGLint numEGLConfigs = 0;
	EGLConfig eglConfigs[1] = {NULL};
	eglChooseConfig(m_EGLDisplay, s_EGLAttributes, eglConfigs, 1, &numEGLConfigs);

	m_EGLSurface = eglCreateWindowSurface(m_EGLDisplay, eglConfigs[0], (EGLNativeWindowType)hWindow, NULL);
	if (m_EGLSurface == EGL_NO_SURFACE) return false;

	m_EGLContext = eglCreateContext(m_EGLDisplay, eglConfigs[0], EGL_NO_CONTEXT, s_EGLContextAttributes);
	if (m_EGLContext == EGL_NO_CONTEXT) return false;

	eglMakeCurrent(m_EGLDisplay, m_EGLSurface, m_EGLSurface, m_EGLContext);

	// set view port
	int winWidth = IConfig::GetInstance().GetInt("WINDOW_WIDTH");
	int winHeight = IConfig::GetInstance().GetInt("WINDOW_HEIGHT");
	glViewport(0, 0, winWidth, winHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

void RenderDevice_Impl::TerminateEGL()
{
	if (m_EGLDisplay)
	{
		eglMakeCurrent(m_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
		eglDestroySurface(m_EGLDisplay, m_EGLSurface);
		eglDestroyContext(m_EGLDisplay, m_EGLContext);
		eglTerminate(m_EGLDisplay);
	}

	m_EGLDisplay = NULL;
	m_EGLSurface = NULL;
	m_EGLContext = NULL;
}
