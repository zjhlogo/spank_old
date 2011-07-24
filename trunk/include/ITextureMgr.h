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
#include "IMgr.h"

class ITextureMgr : public IMgr
{
public:
	static ITextureMgr& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();
	ITexture* CreateTexture(const char* pszFileName);

private:
	ITextureMgr();
	virtual ~ITextureMgr();

};

#endif // __ITEXTUREMGR_H__
