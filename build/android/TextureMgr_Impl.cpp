/*!
 * \file TextureMgr_Impl.cpp
 * \date 23-07-2011 13:23:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TextureMgr_Impl.h"

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
	// TODO: 
	return true;
}

void TextureMgr_Impl::Terminate()
{
	// TODO: 
}

ITexture* TextureMgr_Impl::CreateTexture(const char* pszFileName)
{
	// TODO: 
	return NULL;
}
