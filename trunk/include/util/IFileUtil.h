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
#include "ISingleton.h"

class IFileUtil : public ISingleton
{
public:
	DECLARE_RTTI(IFileUtil, ISingleton);

	static IFileUtil& GetInstance();

	virtual StreamReader* LoadFile(const char* pszFileName) = 0;

};
#endif // __IFILEUTIL_H__
