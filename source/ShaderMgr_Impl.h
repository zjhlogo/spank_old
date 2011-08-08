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
#include <map>

class ShaderMgr_Impl : public IShaderMgr
{
public:
	typedef std::map<int, IShader*> TM_SHADER;

public:
	ShaderMgr_Impl();
	virtual ~ShaderMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual IShader* CreateShader(const char* pszShaderFile);

private:
	IShader* InternalCreateShader(int nShaderID, const char* pszVertexShaderFile, const char* pszFregmentShaderFile, const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);
	IVertexAttribute* InternalCreateVertexAttribute(const IVertexAttribute::ATTRIBUTE_ITEM* pAttrItems);
	IShader* FindShader(int nID);

private:
	TM_SHADER m_mapShader;

};
#endif // __SHADERMGR_IMPL_H__
