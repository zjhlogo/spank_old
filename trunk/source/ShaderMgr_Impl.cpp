/*!
 * \file ShaderMgr_Impl.cpp
 * \date 7-25-2011 10:16:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ShaderMgr_Impl.h"

IShaderMgr& IShaderMgr::GetInstance()
{
	static ShaderMgr_Impl s_ShaderMgr_Impl;
	return s_ShaderMgr_Impl;
}

ShaderMgr_Impl::ShaderMgr_Impl()
{
	// TODO: 
}

ShaderMgr_Impl::~ShaderMgr_Impl()
{
	// TODO: 
}

bool ShaderMgr_Impl::Initialize()
{
	// TODO: 
	return true;
}

void ShaderMgr_Impl::Terminate()
{
	// TODO: 
}

IShader* ShaderMgr_Impl::CreateShaderFromFiles(const char* pszVertexShaderFile, const char* pszFregmentShaderFile)
{
	// TODO: 
	return NULL;
}

IShader* ShaderMgr_Impl::CreateShader(const char* pszVertexShader, const char* pszFregmentShader)
{
	// TODO: 
	return NULL;
}
