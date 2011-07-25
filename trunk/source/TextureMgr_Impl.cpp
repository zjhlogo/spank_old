/*!
 * \file TextureMgr_Impl.cpp
 * \date 7-25-2011 10:19:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TextureMgr_Impl.h"
#include "Texture_Impl.h"

ITextureMgr& ITextureMgr::GetInstance()
{
	static TextureMgr_Impl s_TextureMgr_Impl;
	return s_TextureMgr_Impl;
}

TextureMgr_Impl::TextureMgr_Impl()
{
	// TODO: 
}

TextureMgr_Impl::~TextureMgr_Impl()
{
	// TODO: 
}

bool TextureMgr_Impl::Initialize()
{
	return true;
}

void TextureMgr_Impl::Terminate()
{
	// TODO: 
}

ITexture* TextureMgr_Impl::CreateTexture(const char* pszFileName)
{
	Texture_Impl* pTexture = new Texture_Impl(pszFileName);
	return pTexture;
}
