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
#include <tinyxml-2.6.2/tinyxml.h>

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

IShader* ShaderMgr_Impl::CreateShader(const char* pszShaderFile)
{
	StreamReader* pReader = IFileMgr::GetInstance().LoadFile(pszShaderFile);
	if (!pReader) return NULL;

	TiXmlDocument doc;
	doc.Parse((const char*)pReader->GetBuffer());
	SAFE_RELEASE(pReader);
	if (doc.Error()) return NULL;

	// parse the xml files
	TiXmlElement* pElmShader = doc.RootElement();
	if (!pElmShader) return NULL;

	int nShaderID = 0;
	pElmShader->Attribute("id", &nShaderID);
	if (nShaderID <= 0) return NULL;

	IShader* pShader = FindShader(nShaderID);
	if (pShader)
	{
		pShader->IncRef();
		return pShader;
	}

	const char* pszVertexShader = NULL;
	pszVertexShader = pElmShader->Attribute("vertex_shader");
	if (!pszVertexShader) return NULL;

	const char* pszFregmentShader = NULL;
	pszFregmentShader = pElmShader->Attribute("fregment_shader");
	if (!pszFregmentShader) return NULL;

	TiXmlElement* pElmAttrs = pElmShader->FirstChildElement("attributes");
	if (!pElmAttrs) return NULL;

	IVertexAttribute::ATTRIBUTE_ITEM attrItems[IVertexAttribute::MAX_ATTRIBUTES+1];
	int nAttrIndex = 0;

	TiXmlElement* pElmAttr = pElmAttrs->FirstChildElement("attribute");
	while (pElmAttr)
	{
		int nSize = 0;
		pElmAttr->Attribute("size", &nSize);
		if (nSize <= 0) return NULL;

		const char* pszAttrName = pElmAttr->Attribute("name");
		if (!pszAttrName) return NULL;

		attrItems[nAttrIndex].nSize = nSize;
		attrItems[nAttrIndex].eItemType = IVertexAttribute::AT_FLOAT;
		strncpy(attrItems[nAttrIndex].szParamName, pszAttrName, IVertexAttribute::MAX_NAME_LENGTH);
		attrItems[nAttrIndex].szParamName[IVertexAttribute::MAX_NAME_LENGTH-1] = '\0';

		++nAttrIndex;
		pElmAttr = pElmAttr->NextSiblingElement("attribute");
	}

	if (nAttrIndex <= 0) return NULL;

	attrItems[nAttrIndex].nSize = 0;
	attrItems[nAttrIndex].eItemType = IVertexAttribute::AT_UNKNOWN;
	attrItems[nAttrIndex].nOffset = 0;
	attrItems[nAttrIndex].szParamName[0] = '\0';

	return InternalCreateShader(nShaderID, pszVertexShader, pszFregmentShader, attrItems);
}

IShader* ShaderMgr_Impl::InternalCreateShader(int nShaderID, const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	StreamReader* pVertexShader = IFileMgr::GetInstance().LoadFile(pszVertexShaderFile);
	if (!pVertexShader || !pVertexShader->IsOK())
	{
		SAFE_RELEASE(pVertexShader);
		return NULL;
	}

	StreamReader* pFregmentShader = IFileMgr::GetInstance().LoadFile(pszFregmentShaderFile);
	if (!pFregmentShader || !pFregmentShader->IsOK())
	{
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pFregmentShader);
		return NULL;
	}

	IVertexAttribute* pVertAttrib = InternalCreateVertexAttribute(pAttrItems);
	if (!pVertAttrib || !pVertAttrib->IsOK())
	{
		SAFE_RELEASE(pVertAttrib);
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pFregmentShader);
		return NULL;
	}

	Shader_Impl* pShader = new Shader_Impl(pVertexShader, pFregmentShader, pVertAttrib);
	if (!pShader || !pShader->IsOK())
	{
		SAFE_DELETE(pShader);
		SAFE_RELEASE(pVertAttrib);
		SAFE_RELEASE(pVertexShader);
		SAFE_RELEASE(pFregmentShader);
		return NULL;
	}

	// cache the shader
	m_mapShader.insert(std::make_pair(nShaderID, pShader));

	return pShader;
}

IVertexAttribute* ShaderMgr_Impl::InternalCreateVertexAttribute(const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems)
{
	VertexAttribute_Impl* pVertAttr = new VertexAttribute_Impl(pAttrItems);
	if (!pVertAttr || !pVertAttr->IsOK())
	{
		SAFE_DELETE(pVertAttr);
		return NULL;
	}

	return pVertAttr;
}

IShader* ShaderMgr_Impl::FindShader(int nID)
{
	TM_SHADER::iterator itfound = m_mapShader.find(nID);
	if (itfound == m_mapShader.end()) return NULL;

	return itfound->second;
}
