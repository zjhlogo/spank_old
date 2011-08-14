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
#include "BaseTypeEx.h"

class IShaderMgr : public IMgr
{
public:
	static IShaderMgr& GetInstance();

	virtual IShader* CreateShader(const char* pszShaderFile) = 0;
	virtual IShader* CreateShader(int nShaderID = SSI_DEFAULT) = 0;

};
#endif // __ISHADERMGR_H__
