/*!
 * \file ShaderMgr_Impl.h
 * \date 7-25-2011 10:15:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SHADERMGR_IMPL_H__
#define __SHADERMGR_IMPL_H__

#include <IShaderMgr.h>

class ShaderMgr_Impl : public IShaderMgr
{
public:
	ShaderMgr_Impl();
	virtual ~ShaderMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual IShader* CreateShaderFromFiles(const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);
	virtual IShader* CreateShaderFromBuffers(const char* pszVertexShader, const char* pszFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);
	virtual IShader* CreateShaderFromStreams(StreamReader* pVertexShader, StreamReader* pFregmentShader, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);

	virtual IVertexAttribute* CreateVertexAttribute(const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);

};
#endif // __SHADERMGR_IMPL_H__
