/*!
 * \file IRenderDevice.h
 * \date 23-07-2011 08:29:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERDEVICE_H__
#define __IRENDERDEVICE_H__

#include "IMgr.h"

class IRenderDevice : public IMgr
{
public:
	static IRenderDevice& GetInstance();

	virtual int GetSurfaceWidth() const = 0;
	virtual int GetSurfaceHeight() const = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;
};
#endif // __IRENDERDEVICE_H__
