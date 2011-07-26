/*!
 * \file IShader.h
 * \date 7-25-2011 9:54:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISHADER_H__
#define __ISHADER_H__

#include "IObject.h"
#include "ITexture.h"
#include "math/Matrix4x4.h"

class IShader : public IObject
{
public:
	virtual bool SetMatrix4x4(const char* pszParamName, const Matrix4x4* pMat) = 0;
	virtual bool SetTexture(const char* pszParamName, ITexture* pTexture) = 0;
	virtual bool Commit(const void* pVerts) = 0;
};

#endif // __ISHADER_H__
