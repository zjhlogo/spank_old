/*!
 * \file FileUtil_Android_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil_Android_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>

IFileUtil& IFileUtil::GetInstance()
{
	static FileUtil_Android_Impl s_FileUtil_Android_Impl;
	return s_FileUtil_Android_Impl;
}

FileUtil_Android_Impl::FileUtil_Android_Impl()
{
	m_pMainFile = NULL;
}

FileUtil_Android_Impl::~FileUtil_Android_Impl()
{
	// TODO: 
}

bool FileUtil_Android_Impl::Initialize()
{
	const char* pszPackageFilePath = ConfigUtil::GetInstance().GetString("ANDROID_RESOURCE_PACKAGE");
	if (!pszPackageFilePath || strlen(pszPackageFilePath) <= 0)
	{
		LOGE("invalid resource package path");
		return false;
	}

	m_pMainFile = unzOpen(pszPackageFilePath);
	if (!m_pMainFile)
	{
		LOGE("open resource package file failed: %s", pszPackageFilePath);
		return false;
	}

	m_strRootPath = ConfigUtil::GetInstance().GetString("RESOURCE_DIR", "assets/");
	LOGD("resource directory: %s", m_strRootPath.c_str());

	return true;
}

void FileUtil_Android_Impl::Terminate()
{
	if (m_pMainFile)
	{
		unzClose(m_pMainFile);
		m_pMainFile = NULL;
	}
}

StreamReader* FileUtil_Android_Impl::LoadFile(const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return NULL;

	std::string strFullPath = m_strRootPath + pszFileName;

	int nRet = unzLocateFile(m_pMainFile, strFullPath.c_str(), 1);
	if (nRet != UNZ_OK)
	{
		LOGE("locate file failed: %s", strFullPath.c_str());
		return NULL;
	}

	char szFilePath[MAX_FILE_PATH];
	unz_file_info fileInfo;
	nRet = unzGetCurrentFileInfo(m_pMainFile, &fileInfo, szFilePath, sizeof(szFilePath), NULL, 0, NULL, 0);
	if (nRet != UNZ_OK)
	{
		LOGE("get file info failed: %s", strFullPath.c_str());
		return NULL;
	}

	nRet = unzOpenCurrentFile(m_pMainFile);
	if (nRet != UNZ_OK)
	{
		LOGE("open file failed: %s", szFilePath);
		return NULL;
	}

	int nFileSize = fileInfo.uncompressed_size;
	char* pszBuffer = new char[nFileSize+1];
	int nReadSize = unzReadCurrentFile(m_pMainFile, pszBuffer, nFileSize);
	if (nReadSize != nFileSize)
	{
		LOGE("read size miss-match: %d/%d read", nReadSize, nFileSize);
	}
	unzCloseCurrentFile(m_pMainFile);

	pszBuffer[nFileSize] = '\0';

	StreamReader* pStreamReader = new StreamReader(pszBuffer, nFileSize, true);
	return pStreamReader;
}
