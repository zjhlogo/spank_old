/*!
 * \file ShaderMgr_Impl.cpp
 * \date 7-25-2011 10:16:29
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "ShaderMgr_Impl.h"
#include "Shader_Impl.h"
#include "VertexAttribute_Impl.h"
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

IShader* ShaderMgr_Impl::CreateShaderFromFiles(const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	StreamReader* pVertexShader = IFileMgr::GetInstance().LoadFile(pszVertexShaderFile);
	StreamReader* pFregmentShader = IFileMgr::GetInstance().LoadFile(pszFregmentShaderFile);

	IShader* pShader = CreateShaderFromStreams(pVertexShader, pFregmentShader, pAttrItems);

	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pFregmentShader);
	return pShader;
}

IShader* ShaderMgr_Impl::CreateShaderFromBuffers(const char* pszVertexShader, const char* pszFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	StreamReader* pVertexShader = new StreamReader(pszVertexShader, strlen(pszVertexShader)+1, false);
	StreamReader* pFregmentShader = new StreamReader(pszFregmentShader, strlen(pszFregmentShader)+1, false);

	IShader* pShader = CreateShaderFromStreams(pVertexShader, pFregmentShader, pAttrItems);

	SAFE_RELEASE(pVertexShader);
	SAFE_RELEASE(pFregmentShader);
	return pShader;
}

IShader* ShaderMgr_Impl::CreateShaderFromStreams(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	if (!pVertexShader || !pVertexShader->IsOK()) return NULL;
	if (!pFregmentShader || !pFregmentShader->IsOK()) return NULL;

	Shader_Impl* pShader = new Shader_Impl(pVertexShader, pFregmentShader, pAttrItems);
	if (!pShader || !pShader->IsOK())
	{
		SAFE_DELETE(pShader);
		return NULL;
	}

	return pShader;
}

IVertexAttribute* ShaderMgr_Impl::CreateVertexAttribute(const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	VertexAttribute_Impl* pVertAttr = new VertexAttribute_Impl(pAttrItems);
	if (!pVertAttr || !pVertAttr->IsOK())
	{
		SAFE_DELETE(pVertAttr);
		return NULL;
	}

	return pVertAttr;
}
