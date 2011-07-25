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

	virtual void Update(float dt) = 0;
	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;
};
#endif // __ICORE_H__
