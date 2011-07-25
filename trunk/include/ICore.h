/*!
 * \file ICore.h
 * \date 23-07-2011 11:14:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ICORE_H__
#define __ICORE_H__

#include "IMgr.h"

class ICore : public IMgr
{
public:
	static ICore& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	void Update(float dt);
	void PreRender();
	void Render();
	void PostRender();
};
#endif // __ICORE_H__
