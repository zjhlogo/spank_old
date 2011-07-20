/*!
 * \file FileMgr_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileMgr_Impl.h"

IFileMgr& IFileMgr::GetInstance()
{
	static FileMgr_Impl s_FileMgr;
	return s_FileMgr;
}

FileMgr_Impl::FileMgr_Impl()
{
	m_pMainFile = NULL;
}

FileMgr_Impl::~FileMgr_Impl()
{
	Terminate();
}

bool FileMgr_Impl::Initialize(const char* pszMainFilePath)
{
	Terminate();

	if (!pszMainFilePath || strlen(pszMainFilePath) <= 0) return false;

	m_pMainFile = unzOpen(pszMainFilePath);
	if (!m_pMainFile)
	{
		// TODO: logout
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

bool FileMgr_Impl::ReadFile(char** pszBufferOut, uint* nSizeOut, const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return false;

	int nRet = unzLocateFile(m_pMainFile, pszFileName, 1);
	if (nRet != UNZ_OK)
	{
		// TODO: logout
		return false;
	}

	char szFilePath[260];
	unz_file_info fileInfo;
	nRet = unzGetCurrentFileInfo(m_pMainFile, &fileInfo, szFilePath, sizeof(szFilePath), NULL, 0, NULL, 0);
	if (nRet != UNZ_OK)
	{
		// TODO: logout
		return false;
	}

	nRet = unzOpenCurrentFile(m_pMainFile);
	if (nRet != UNZ_OK)
	{
		// TODO: logout
		return 0;
	}

	int nFileSize = fileInfo.uncompressed_size;
	char* pszBuffer = new char[nFileSize+1];
	int nReadSize = unzReadCurrentFile(m_pMainFile, pszBuffer, nFileSize);
	unzCloseCurrentFile(m_pMainFile);

	pszBuffer[nFileSize] = '\0';
	(*pszBufferOut) = pszBuffer;
	(*nSizeOut) = nFileSize;

	return true;
}
