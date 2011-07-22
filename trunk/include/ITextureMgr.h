/*!
 * \file ITextureMgr.h
 * \date 7-22-2011 10:45:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ITEXTUREMGR_H__
#define __ITEXTUREMGR_H__

#include "ITexture.h"

class ITextureMgr
{
public:
	static ITextureMgr& GetInstance();

	virtual bool Initialize() = 0;
	virtual void Terminate() = 0;

	virtual ITexture* CreateTexture(const char* pszFileName) = 0;
};

#endif // __ITEXTUREMGR_H__
