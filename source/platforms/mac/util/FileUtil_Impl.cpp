/*!
 * \file FileUtil_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileUtil_Impl.h"
#include <util/ConfigUtil.h>
#include <util/IDebugUtil.h>

IFileUtil& IFileUtil::GetInstance()
{
	static FileUtil_Impl s_FileUtil_Impl;
	return s_FileUtil_Impl;
}

FileUtil_Impl::FileUtil_Impl()
{
	// TODO: 
}

FileUtil_Impl::~FileUtil_Impl()
{
	Terminate();
}

bool FileUtil_Impl::Initialize()
{
	const char* pszResourceDir = ConfigUtil::GetInstance().GetString("RESOURCE_DIR");
	if (!pszResourceDir || strlen(pszResourceDir) <= 0)
	{
		LOGE("invalid resource dir");
		return false;
	}
	
	m_strRootPath = pszResourceDir;
	m_strRootPath += "/";
	return true;
}

void FileUtil_Impl::Terminate()
{
	// TODO: 
}

StreamReader* FileUtil_Impl::LoadFile(const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return NULL;
	
	std::string strFullPath = m_strRootPath + pszFileName;
	
	FILE* pFile = fopen(strFullPath.c_str(), "rb");
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
	
	if (nReadSize < nFileSize)
	{
		SAFE_DELETE_ARRAY(pszBuffer);
		return NULL;
	}
	
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
