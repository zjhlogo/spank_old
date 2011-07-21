/*!
 * \file WinMain.cpp
 * \date 7-21-2011 11:55:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "WinMain.h"
#include "EGL/egl.h"
#include <IGameMain.h>

EGLDisplay g_EGLDisplay = NULL;
EGLSurface g_EGLSurface = NULL;
EGLContext g_EGLContext = NULL;

LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
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

HWND CreateMainWindow(int uiWidth, int uiHeight)
{
	WNDCLASS wc;
	RECT wRect;
	HWND sWindow;
	HINSTANCE hInstance;

	wRect.left = 0L;
	wRect.right = (long)uiWidth;
	wRect.top = 0L;
	wRect.bottom = (long)uiHeight;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
	wc.lpfnWndProc = (WNDPROC)MainWndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = NULL;
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "OGLES";

	RegisterClass(&wc);

	AdjustWindowRectEx(&wRect, WS_OVERLAPPEDWINDOW, FALSE, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

	sWindow = CreateWindowEx(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
		"OGLES",
		"main",
		WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
		0, 0, uiWidth, uiHeight,
		NULL, NULL, hInstance, NULL);

	ShowWindow(sWindow, SW_SHOW);
	SetForegroundWindow(sWindow);
	SetFocus(sWindow);

	return sWindow;
}

void EnterMainWindowLoop()
{
	MSG msg;
	memset(&msg, 0, sizeof(msg));
	bool run = true;
	while (run)
	{
		while(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) 
		{
			if(msg.message == WM_QUIT)
			{
				run = false;
				break;
			}

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		// TODO: update
		IGameMain::GetInstance().Update(0.0f);
		// TODO: render
		IGameMain::GetInstance().Render();

		eglSwapBuffers(g_EGLDisplay, g_EGLSurface);
	}
}

bool InitializeEGL(HWND hWindow)
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

	g_EGLDisplay = eglGetDisplay(hDisplay);
	eglInitialize(g_EGLDisplay, NULL, NULL);

	EGLint numEGLConfigs = 0;
	EGLConfig eglConfigs[1] = {NULL};
	eglChooseConfig(g_EGLDisplay, s_EGLAttributes, eglConfigs, 1, &numEGLConfigs);

	g_EGLSurface = eglCreateWindowSurface(g_EGLDisplay, eglConfigs[0], (EGLNativeWindowType)hWindow, NULL);
	if (g_EGLSurface == EGL_NO_SURFACE) return false;

	g_EGLContext = eglCreateContext(g_EGLDisplay, eglConfigs[0], EGL_NO_CONTEXT, s_EGLContextAttributes);
	if (g_EGLContext == EGL_NO_CONTEXT) return false;

	eglMakeCurrent(g_EGLDisplay, g_EGLSurface, g_EGLSurface, g_EGLContext);

	return true;
}

void TerminateEGL()
{
	eglMakeCurrent(g_EGLDisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	eglDestroySurface(g_EGLDisplay, g_EGLSurface);
	eglDestroyContext(g_EGLDisplay, g_EGLContext);
	eglTerminate(g_EGLDisplay);
	g_EGLDisplay = NULL;
	g_EGLSurface = NULL;
	g_EGLContext = NULL;
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	HWND hMainWindow = CreateMainWindow(800, 480);
	if (hMainWindow == NULL) return 0;

	if (!InitializeEGL(hMainWindow)) return 0;

	IGameMain::GetInstance().Initialize(800, 480);
	EnterMainWindowLoop();
	IGameMain::GetInstance().Terminate();

	TerminateEGL();
	return 0;
}
