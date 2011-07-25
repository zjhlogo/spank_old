/*!
 * \file ShaderMgr_Impl.cpp
 * \date 7-25-2011 10:16:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ShaderMgr_Impl.h"
#include "Shader_Impl.h"
#include <IFileMgr.h>
#include <string>

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
	StreamReader* pVertexShader = IFileMgr::GetInstance().LoadFile(pszVertexShaderFile);
	StreamReader* pFregmentShader = IFileMgr::GetInstance().LoadFile(pszFregmentShaderFile);

	IShader* pShader = CreateShaderFromStreams(pVertexShader, pFregmentShader);

	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pFregmentShader);
	return pShader;
}

IShader* ShaderMgr_Impl::CreateShaderFromBuffers(const char* pszVertexShader, const char* pszFregmentShader)
{
	StreamReader* pVertexShader = new StreamReader(pszVertexShader, strlen(pszVertexShader)+1, false);
	StreamReader* pFregmentShader = new StreamReader(pszFregmentShader, strlen(pszFregmentShader)+1, false);

	IShader* pShader = CreateShaderFromStreams(pVertexShader, pFregmentShader);

	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pFregmentShader);
	return pShader;
}

IShader* ShaderMgr_Impl::CreateShaderFromStreams(StreamReader* pVertexShader, StreamReader* pFregmentShader)
{
	if (!pVertexShader || !pVertexShader->IsOK()) return NULL;
	if (!pFregmentShader || !pFregmentShader->IsOK()) return NULL;

	Shader_Impl* pShader = new Shader_Impl(pVertexShader, pFregmentShader);
	if (!pShader || !pShader->IsOK())
	{
		SAFE_DELETE(pShader);
		return NULL;
	}

	return pShader;
}
