/*!
 * \file StringUtil.h
 * \date 14-08-2011 11:21:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __STRINGUTIL_H__
#define __STRINGUTIL_H__

#include "../BaseType.h"

class StringUtil
{
public:
	static void ZeroMemory(void* pBuffer, int nSize);
	static bool CopyString(char* pszBufferOut, int nBufferSize, const char* pszIn);
	static int StringLength(const char* pszString);
	static bool IsEqual(const char* psz1, const char* psz2);
	static int Utf8ToUnicode(ushort* pUnicodeOut, int nUnicodeLength, const char* pszUtf8);

};
#endif // __STRINGUTIL_H__
