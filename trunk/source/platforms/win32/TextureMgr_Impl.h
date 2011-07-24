/*!
 * \file TextureMgr_Impl.h
 * \date 7-22-2011 12:53:41
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __TEXTUREMGR_IMPL_H__
#define __TEXTUREMGR_IMPL_H__

#include <ITextureMgr.h>

class TextureMgr_Impl : public ITextureMgr
{
public:
	TextureMgr_Impl();
	virtual ~TextureMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual ITexture* CreateTexture(const char* pszFileName);

};
#endif // __TEXTUREMGR_IMPL_H__