/*!
 * \file FileMgr_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileMgr_Impl.h"
#include <IDebugUtil.h>
#include <IConfig.h>
#include <util/StreamWriter.h>

IFileMgr& IFileMgr::GetInstance()
{
	static FileMgr_Impl s_FileMgr_Impl;
	return s_FileMgr_Impl;
}

FileMgr_Impl::FileMgr_Impl()
{
	m_pMainFile = NULL;
}

FileMgr_Impl::~FileMgr_Impl()
{
	// TODO: 
}

bool FileMgr_Impl::Initialize()
{
	const char* pszPackageFilePath = IConfig::GetInstance().GetString("ANDROID_RESOURCE_PACKAGE");
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

	return true;
}

void FileMgr_Impl::Terminate()
{
	if (m_pMainFile)
	{
		unzClose(m_pMainFile);
		m_pMainFile = NULL;
	}
}

StreamReader* FileMgr_Impl::LoadFile(const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0)
	{
		LOGE("invalid file");
		return NULL;
	}

	int nRet = unzLocateFile(m_pMainFile, pszFileName, 1);
	if (nRet != UNZ_OK)
	{
		LOGE("locate file failed: %s", pszFileName);
		return NULL;
	}

	char szFilePath[MAX_FILE_PATH];
	unz_file_info fileInfo;
	nRet = unzGetCurrentFileInfo(m_pMainFile, &fileInfo, szFilePath, sizeof(szFilePath), NULL, 0, NULL, 0);
	if (nRet != UNZ_OK)
	{
		LOGE("get file info failed: %s", pszFileName);
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
		LOGE("read size mismatch: %d/%d read", nReadSize, nFileSize);
	}
	unzCloseCurrentFile(m_pMainFile);

	pszBuffer[nFileSize] = '\0';

	StreamReader* pStreamReader = new StreamReader(pszBuffer, nFileSize, true);
	return pStreamReader;
}
