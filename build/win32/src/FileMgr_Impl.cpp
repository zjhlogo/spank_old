/*!
 * \file FileMgr_Impl.cpp
 * \date 7-20-2011 10:59:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "FileMgr_Impl.h"
#include <stdio.h>
#include <string.h>

IFileMgr& IFileMgr::GetInstance()
{
	static FileMgr_Impl s_FileMgr;
	return s_FileMgr;
}

FileMgr_Impl::FileMgr_Impl()
{
	// TODO: 
}

FileMgr_Impl::~FileMgr_Impl()
{
	Terminate();
}

bool FileMgr_Impl::Initialize(const char* pszMainFilePath)
{
	Terminate();

	return true;
}

void FileMgr_Impl::Terminate()
{
	// TODO: 
}

bool FileMgr_Impl::ReadFile(char** pszBufferOut, uint* nSizeOut, const char* pszFileName)
{
	if (!pszFileName || strlen(pszFileName) <= 0) return false;

	FILE* pFile = NULL;
	fopen_s(&pFile, pszFileName, "rb");
	if (pFile == NULL) return false;

	fseek(pFile, 0, SEEK_END);
	uint nFileSize = ftell(pFile);
	fseek(pFile, 0, SEEK_SET);

	char* pszBuffer = new char[nFileSize+1];
	int nReadSize = fread(pszBuffer, 1, nFileSize, pFile);
	fclose(pFile);

	pszBuffer[nFileSize] = '\0';
	(*pszBufferOut) = pszBuffer;
	(*nSizeOut) = nFileSize;

	return true;
}
