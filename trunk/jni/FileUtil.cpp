/*!
 * \file FileUtil.cpp
 * \date 7-19-2011 14:48:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil.h"
#include "DebugUtil.h"
#include "unzip.h"
#include <string.h>

char FileUtil::m_szPackagePath[FileUtil::MAX_FILE_PATH] = {'\0'};

bool FileUtil::ReadFile(char** pBufferOut, int& nSizeOut, const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) == 0) return false;

	unzFile pFile = unzOpen(m_szPackagePath);
	if (!pFile)
	{
		LOGE("unzOpen %s Failed", m_szPackagePath);
		return false;
	}

	int nRet = unzLocateFile(pFile, pszFileName, 1);
	if (nRet != UNZ_OK)
	{
		LOGE("unzLocateFile %s Failed", pszFileName);
		return false;
	}

	char szFilePathA[MAX_FILE_PATH];
	unz_file_info FileInfo;
	nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
	if (nRet != UNZ_OK)
	{
		LOGE("unzGetCurrentFileInfo %s Failed", pszFileName);
		return false;
	}

	nRet = unzOpenCurrentFile(pFile);
	if (nRet != UNZ_OK)
	{
		LOGE("unzOpenCurrentFile %s Failed", pszFileName);
		return false;
	}

	char* pBuffer = new char[FileInfo.uncompressed_size+1];
	int nSize = unzReadCurrentFile(pFile, pBuffer, FileInfo.uncompressed_size);
	if (nSize < 0 || nSize != FileInfo.uncompressed_size)
	{
		delete[] pBuffer;
		pBuffer = NULL;
		nSize = 0;
		LOGE("unzReadCurrentFile %s Failed", pszFileName);
		return false;
	}
	unzCloseCurrentFile(pFile);

	if (pFile)
	{
		unzClose(pFile);
		pFile = NULL;
	}

	pBuffer[nSize] = '\0';
	*pBufferOut = pBuffer;
	nSizeOut = nSize;

	return true;
}

void FileUtil::SetPackagePath(const char* pszPackagePath)
{
	strcpy(m_szPackagePath, pszPackagePath);
	LOGI("FileUtil::SetPackagePath %s", m_szPackagePath);
}

const char* FileUtil::GetPackagePath()
{
	return m_szPackagePath;
}
