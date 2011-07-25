/*!
 * \file IShaderMgr.h
 * \date 7-25-2011 9:54:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISHADERMGR_H__
#define __ISHADERMGR_H__

#include "IMgr.h"
#include "IShader.h"
#include "IVertexAttribute.h"
#include "util/StreamReader.h"

class IShaderMgr : public IMgr
{
public:
	static IShaderMgr& GetInstance();

	virtual IShader* CreateShaderFromFiles(const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems) = 0;
	virtual IShader* CreateShaderFromBuffers(const char* pszVertexShader, const char* pszFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems) = 0;
	virtual IShader* CreateShaderFromStreams(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems) = 0;

	virtual IVertexAttribute* CreateVertexAttribute(const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems) = 0;
};
#endif // __ISHADERMGR_H__
