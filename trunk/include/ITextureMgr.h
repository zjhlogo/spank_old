/*!
 * \file ITextureMgr.h
 * \date 7-22-2011 10:45:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ITEXTUREMGR_H__
#define __ITEXTUREMGR_H__

#include "IMgr.h"
#include "ITexture.h"

class ITextureMgr : public IMgr
{
public:
	DECLARE_RTTI(ITextureMgr, IMgr);

	static ITextureMgr& GetInstance();

	virtual ITexture* CreateTexture(const char* pszFileName, TEXTURE_SAMPLE_TYPE eSample = TST_POINT) = 0;
};

#endif // __ITEXTUREMGR_H__
