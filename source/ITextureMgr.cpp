/*!
 * \file ITextureMgr.cpp
 * \date 24-07-2011 17:01:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ITextureMgr.h>
#include "Texture_Impl.h"

ITextureMgr& ITextureMgr::GetInstance()
{
	static ITextureMgr s_ITextureMgr;
	return s_ITextureMgr;
}

ITextureMgr::ITextureMgr()
{
	// TODO: 
}

ITextureMgr::~ITextureMgr()
{
	// TODO: 
}

bool ITextureMgr::Initialize()
{
	return true;
}

void ITextureMgr::Terminate()
{
	// TODO: 
}

ITexture* ITextureMgr::CreateTexture(const char* pszFileName)
{
	Texture_Impl* pTexture = new Texture_Impl(pszFileName);
	return pTexture;
}
