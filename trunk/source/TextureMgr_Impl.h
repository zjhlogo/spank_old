/*!
 * \file TextureMgr_Impl.h
 * \date 7-25-2011 10:17:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __TEXTUREMGR_IMPL_H__
#define __TEXTUREMGR_IMPL_H__

#include <ITextureMgr.h>
#include <msg/IMsgBase.h>
#include <string>
#include <map>

class TextureMgr_Impl : public ITextureMgr
{
public:
	typedef std::map<std::string, ITexture*> TM_TEXTURE;

public:
	TextureMgr_Impl();
	virtual ~TextureMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual ITexture* CreateTexture(const char* pszFileName, ITexture::SAMPLE_TYPE eSample = ITexture::SAMPLE_POINT);

private:
	ITexture* FindTexture(const char* pszFileName);
	bool OnTextureDestroied(IMsgBase* pMsg);

private:
	TM_TEXTURE m_TextureMap;

};
#endif // __TEXTUREMGR_IMPL_H__
