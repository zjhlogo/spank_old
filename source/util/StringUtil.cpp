/*!
 * \file StringUtil.cpp
 * \date 14-08-2011 11:22:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <util/StringUtil.h>
#include <string.h>

void StringUtil::ZeroMemory(void* pBuffer, int nSize)
{
	memset(pBuffer, 0, nSize);
}

bool StringUtil::CopyString(char* pszBufferOut, int nBufferSize, const char* pszIn)
{
	if (!pszBufferOut || !pszIn || nBufferSize <= 0) return false;

	while ((--nBufferSize) > 0 && *pszIn)
	{
		*(pszBufferOut++) = (*pszIn++);
	}

	*pszBufferOut = '\0';
	return true;
}

bool StringUtil::IsEqual(const char* psz1, const char* psz2)
{
	if (strcmp(psz1, psz2) != 0) return false;
	return true;
}
