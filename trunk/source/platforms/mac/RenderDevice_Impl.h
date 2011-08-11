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

class RenderDevice_Impl : public IRenderDevice
{
public:
	RenderDevice_Impl();
	virtual ~RenderDevice_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual int GetSurfaceWidth() const;
	virtual int GetSurfaceHeight() const;

	virtual SCREEN_ROTATION GetScreenRotation() const;

	virtual void BeginRender();
	virtual void EndRender();

private:
	int m_nSurfaceWidth;
	int m_nSurfaceHeight;
	SCREEN_ROTATION m_eScreenRotation;
	
};
#endif // __RENDERDEVICE_IMPL_H__