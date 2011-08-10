/*!
 * \file IFileUtil.h
 * \date 10-08-2011 21:46:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IFILEUTIL_H__
#define __IFILEUTIL_H__

#include "../StreamReader.h"
#include "IMgr.h"

class IFileUtil : public IMgr
{
public:
	static IFileUtil& GetInstance();

	virtual StreamReader* LoadFile(const char* pszFileName) = 0;
	virtual StreamReader* LoadImageFile(const char* pszFileName, uint* pnWidth, uint* pnHeight) = 0;

};
#endif // __IFILEUTIL_H__
