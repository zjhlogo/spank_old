/*!
 * \file FileMgr_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileMgr_Impl.h"
#include <IConfig.h>
#include <IDebugUtil.h>
#include <stdio.h>
#include <string.h>

IFileMgr& IFileMgr::GetInstance()
{
	static FileMgr_Impl s_FileMgr_Impl;
	return s_FileMgr_Impl;
}

FileMgr_Impl::FileMgr_Impl()
{
	// TODO: 
}

FileMgr_Impl::~FileMgr_Impl()
{
	Terminate();
}

bool FileMgr_Impl::Initialize()
{
	m_strRootPath = IConfig::GetInstance().GetString("RESOURCE_DIR", ".\\data\\");
	return true;
}

void FileMgr_Impl::Terminate()
{
	// TODO: 
}

StreamReader* FileMgr_Impl::LoadFile(const char* pszFileName)
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
