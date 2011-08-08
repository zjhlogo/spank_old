/*!
 * \file RenderDevice_Impl.h
 * \date 23-07-2011 10:32:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERDEVICE_IMPL_H__
#define __RENDERDEVICE_IMPL_H__

#include <IRenderDevice.h>
#include <Windows.h>
#include <EGL/egl.h>

class RenderDevice_Impl : public IRenderDevice
{
public:
	RenderDevice_Impl();
	virtual ~RenderDevice_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual int GetSurfaceWidth() const;
	virtual int GetSurfaceHeight() const;

	virtual void BeginRender();
	virtual void EndRender();

private:
	bool InitializeWindow();
	void TerminateWindow();
	static LRESULT CALLBACK MainWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	bool InitializeEGL(HWND hWindow);
	void TerminateEGL();

private:
	EGLDisplay m_EGLDisplay;
	EGLSurface m_EGLSurface;
	EGLContext m_EGLContext;

	HWND m_hWindow;
	int m_nSurfaceWidth;
	int m_nSurfaceHeight;

};
#endif // __RENDERDEVICE_IMPL_H__
