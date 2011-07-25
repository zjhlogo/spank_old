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
#include "util/StreamReader.h"

class IShaderMgr : public IMgr
{
public:
	static IShaderMgr& GetInstance();

	virtual IShader* CreateShaderFromFiles(const char* pszVertexShaderFile, const char* pszFregmentShaderFile) = 0;
	virtual IShader* CreateShaderFromBuffers(const char* pszVertexShader, const char* pszFregmentShader) = 0;
	virtual IShader* CreateShaderFromStreams(StreamReader* pVertexShader, StreamReader* pFregmentShader) = 0;

};
#endif // __ISHADERMGR_H__
