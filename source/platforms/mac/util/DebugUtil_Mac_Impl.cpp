/*!
 * \file DebugUtil_Mac_Impl.cpp
 * \date 7-20-2011 16:47:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DebugUtil_Mac_Impl.h"
#include <stdarg.h>
#include <stdio.h>

IDebugUtil& IDebugUtil::GetInstance()
{
	static DebugUtil_Mac_Impl s_DebugUtil_Mac_Impl;
	return s_DebugUtil_Mac_Impl;
}

DebugUtil_Mac_Impl::DebugUtil_Mac_Impl()
{
	// TODO: 
}

DebugUtil_Mac_Impl::~DebugUtil_Mac_Impl()
{
	// TODO: 
}

bool DebugUtil_Mac_Impl::Initialize()
{
	return true;
}

void DebugUtil_Mac_Impl::Terminate()
{
	// TODO: 
}

void DebugUtil_Mac_Impl::Debug(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	vprintf(format, marker);
	printf("\n");
	va_end(marker);
}

void DebugUtil_Mac_Impl::Info(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);
	
	vprintf(format, marker);
	printf("\n");
	
	va_end(marker);
}

void DebugUtil_Mac_Impl::Error(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);
	
	vprintf(format, marker);
	printf("\n");
	
	va_end(marker);
}
