/*!
 * \file IShader.h
 * \date 7-25-2011 9:54:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISHADER_H__
#define __ISHADER_H__

#include "BaseType.h"
#include "ITexture.h"

class IShader
{
public:
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture) = 0;

};

#endif // __ISHADER_H__
