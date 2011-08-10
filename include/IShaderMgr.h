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

class IShaderMgr : public IMgr
{
public:
	enum SHADER_IDS
	{
		DEFAULT_SHADER = 1,
	};

public:
	static IShaderMgr& GetInstance();

	virtual IShader* CreateShader(const char* pszShaderFile) = 0;
};
#endif // __ISHADERMGR_H__
