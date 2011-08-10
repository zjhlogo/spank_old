/*!
 * \file FileUtil_Impl.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FILEUTIL_IMPL_H__
#define __FILEUTIL_IMPL_H__

#include <util/IFileUtil.h>
#include <string>

class FileUtil_Impl : public IFileUtil
{
public:
	FileUtil_Impl();
	virtual ~FileUtil_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual StreamReader* LoadFile(const char* pszFileName);
	virtual StreamReader* LoadImageFile(const char* pszFileName, uint* pnWidth, uint* pnHeight);

private:
	std::string m_strRootPath;
	
};
#endif // __FILEUTIL_IMPL_H__
