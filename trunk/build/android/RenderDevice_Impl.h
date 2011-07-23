/*!
 * \file RenderDevice_Impl.h
 * \date 23-07-2011 12:43:30
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
	virtual bool Initialize();
	virtual void Terminate();

	virtual void BeginRender();
	virtual void EndRender();

};
#endif // __RENDERDEVICE_IMPL_H__
