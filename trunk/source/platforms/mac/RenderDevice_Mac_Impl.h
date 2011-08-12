/*!
 * \file RenderDevice_Mac_Impl.h
 * \date 23-07-2011 10:32:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERDEVICE_MAC_IMPL_H__
#define __RENDERDEVICE_MAC_IMPL_H__

#include <IRenderDevice.h>

class RenderDevice_Mac_Impl : public IRenderDevice
{
public:
	RenderDevice_Mac_Impl();
	virtual ~RenderDevice_Mac_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual int GetSurfaceWidth() const;
	virtual int GetSurfaceHeight() const;

	virtual void BeginRender();
	virtual void EndRender();

private:
	int m_nSurfaceWidth;
	int m_nSurfaceHeight;
	
};
#endif // __RENDERDEVICE_MAC_IMPL_H__
