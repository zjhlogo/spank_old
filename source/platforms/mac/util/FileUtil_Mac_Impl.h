/*!
 * \file FileUtil_Mac_Impl.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FILEUTIL_MAC_IMPL_H__
#define __FILEUTIL_MAC_IMPL_H__

#include <util/IFileUtil.h>
#include <string>

class FileUtil_Mac_Impl : public IFileUtil
{
public:
	DECLARE_RTTI(FileUtil_Mac_Impl, IFileUtil);

	FileUtil_Mac_Impl();
	virtual ~FileUtil_Mac_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual StreamReader* LoadFile(const char* pszFileName);

private:
	std::string m_strRootPath;
	
};
#endif // __FILEUTIL_MAC_IMPL_H__
