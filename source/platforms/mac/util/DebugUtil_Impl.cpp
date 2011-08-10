/*!
 * \file DebugUtil_Impl.cpp
 * \date 7-20-2011 16:47:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DebugUtil_Impl.h"
#include <stdarg.h>
#include <stdio.h>

IDebugUtil& IDebugUtil::GetInstance()
{
	static DebugUtil_Impl s_DebugUtil_Impl;
	return s_DebugUtil_Impl;
}

bool DebugUtil_Impl::Initialize()
{
	return true;
}

void DebugUtil_Impl::Terminate()
{
	// TODO: 
}

void DebugUtil_Impl::Debug(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	vprintf(format, marker);
	
	va_end(marker);
}

void DebugUtil_Impl::Info(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);
	
	vprintf(format, marker);
	
	va_end(marker);
}

void DebugUtil_Impl::Error(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);
	
	vprintf(format, marker);
	
	va_end(marker);
}
