/*!
 * \file IFileMgr.h
 * \date 7-20-2011 10:27:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IFILEMGR_H__
#define __IFILEMGR_H__

#include "util/StreamReader.h"
#include "IMgr.h"

class IFileMgr : public IMgr
{
public:
	static IFileMgr& GetInstance();

	virtual StreamReader* LoadFile(const char* pszFileName) = 0;
	virtual StreamReader* LoadImageFile(const char* pszFileName, uint* pnWidth, uint* pnHeight) = 0;

};

#endif // __IFILEMGR_H__
