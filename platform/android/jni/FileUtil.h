/*!
 * \file FileUtil.h
 * \date 7-19-2011 14:48:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FILEUTIL_H__
#define __FILEUTIL_H__

class FileUtil
{
public:
	enum CONST_DEFINE
	{
		MAX_FILE_PATH = 260,
	};

public:
	static bool ReadFile(char** pBufferOut, int& nSizeOut, const char* pszFileName);

	static void SetPackagePath(const char* pszPackagePath);
	static const char* GetPackagePath();

private:
	static char m_szPackagePath[MAX_FILE_PATH];

};
#endif // __FILEUTIL_H__
