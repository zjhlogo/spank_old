/*!
 * \file IFileMgr.h
 * \date 7-20-2011 10:27:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IFILEMGR_H__
#define __IFILEMGR_H__

#include "BaseType.h"

class IFileMgr
{
public:
	static IFileMgr& GetInstance();

	virtual bool Initialize(const char* pszMainFilePath) = 0;
	virtual void Terminate() = 0;

	virtual bool ReadFile(char** pszBufferOut, uint* nSizeOut, const char* pszFileName) = 0;
};

#endif // __IFILEMGR_H__
