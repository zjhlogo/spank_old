/*!
 * \file FileUtil_Android_Impl.h
 * \date 7-20-2011 10:58:15
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FILEUTIL_ANDROID_IMPL_H__
#define __FILEUTIL_ANDROID_IMPL_H__

#include <util/IFileUtil.h>
#include "../unzip/unzip.h"
#include <string>

class FileUtil_Android_Impl : public IFileUtil
{
public:
	enum CONST_DEFINE
	{
		MAX_FILE_PATH = 260,
	};

public:
	FileUtil_Android_Impl();
	virtual ~FileUtil_Android_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual StreamReader* LoadFile(const char* pszFileName);

private:
	unzFile m_pMainFile;
	std::string m_strRootPath;

};
#endif // __FILEUTIL_ANDROID_IMPL_H__
