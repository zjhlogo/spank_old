/*!
 * \file FileUtil_Win32_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil_Win32_Impl.h"
#include <util/IDebugUtil.h>
#include <util/ConfigUtil.h>
#include <stdio.h>
#include <string.h>

IFileUtil& IFileUtil::GetInstance()
{
	static FileUtil_Win32_Impl s_FileUtil_Win32_Impl;
	return s_FileUtil_Win32_Impl;
}

FileUtil_Win32_Impl::FileUtil_Win32_Impl()
{
	// TODO: 
}

FileUtil_Win32_Impl::~FileUtil_Win32_Impl()
{
	// TODO: 
}

bool FileUtil_Win32_Impl::Initialize()
{
	m_strRootPath = ConfigUtil::GetInstance().GetString("RESOURCE_DIR", "");
	if (m_strRootPath.empty())
	{
		LOGE("empty resource directory, please set the config of [RESOURCE_DIR]");
		return false;
	}

	LOGD("resource directory: %s", m_strRootPath.c_str());
	return true;
}

void FileUtil_Win32_Impl::Terminate()
{
	// TODO: 
}

StreamReader* FileUtil_Win32_Impl::LoadFile(const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return NULL;

	std::string strFullPath = m_strRootPath + pszFileName;

	FILE* pFile = NULL;
	fopen_s(&pFile, strFullPath.c_str(), "rb");
	if (pFile == NULL)
	{
		LOGE("open file failed: %s", strFullPath.c_str());
		return NULL;
	}

	fseek(pFile, 0, SEEK_END);
	uint nFileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	char* pszBuffer = new char[nFileSize+1];
	int nReadSize = fread(pszBuffer, 1, nFileSize, pFile);
	fclose(pFile);

	pszBuffer[nFileSize] = '\0';

	StreamReader* pStreamReader = new StreamReader(pszBuffer, nFileSize, true);
	if (!pStreamReader || !pStreamReader->IsOK())
	{
		LOGE("create stream reader failed with file size: %d", nFileSize);
		SAFE_DELETE(pStreamReader);
		SAFE_DELETE_ARRAY(pszBuffer);
		return NULL;
	}

	return pStreamReader;
}
