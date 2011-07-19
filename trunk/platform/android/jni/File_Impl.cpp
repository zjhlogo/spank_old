/*!
 * \file File_Impl.cpp
 * \date 19-07-2011 22:33:42
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "File_Impl.h"
#include "unzip/unzip.h"

File_Impl::File_Impl()
{

}

File_Impl::~File_Impl()
{

}

bool File_Impl::OpenFile(const char* pszFileName)
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

uint File_Impl::Read(void* pBuffOut, uint nSize)
{

}

uint File_Impl::Write(const void* pBuffIn, uint nSize)
{

}

uint File_Impl::Seek(uint nOffset)
{

}

uint File_Impl::GetSize() const
{

}

uint File_Impl::Tell() const
{

}
