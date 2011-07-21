/*!
 * \file DebugUtil_Impl.cpp
 * \date 7-20-2011 16:47:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DebugUtil_Impl.h"
#include <Windows.h>
#include <stdio.h>
#include <stdarg.h>

IDebugUtil& IDebugUtil::GetInstance()
{
	static DebugUtil_Impl s_DebugUtil_Impl;
	return s_DebugUtil_Impl;
}

void DebugUtil_Impl::Debug(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[1024];
	vsprintf_s(szOut, 1024, format, marker);
	OutputDebugString(szOut);

	va_end(marker);
}

void DebugUtil_Impl::Info(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[1024];
	vsprintf_s(szOut, 1024, format, marker);
	OutputDebugString(szOut);

	va_end(marker);
}

void DebugUtil_Impl::Error(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[1024];
	vsprintf_s(szOut, 1024, format, marker);
	OutputDebugString(szOut);

	va_end(marker);
}
