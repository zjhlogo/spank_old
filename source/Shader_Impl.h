/*!
 * \file Shader_Impl.h
 * \date 7-25-2011 10:14:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __SHADER_IMPL_H__
#define __SHADER_IMPL_H__

#include <IShader.h>

class Shader_Impl : public IShader
{
public:
	Shader_Impl();
	virtual ~Shader_Impl();

	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture);

};
#endif // __SHADER_IMPL_H__
