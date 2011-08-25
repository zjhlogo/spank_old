/*!
 * \file DebugUtil_Win32_Impl.cpp
 * \date 7-20-2011 16:47:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "DebugUtil_Win32_Impl.h"
#include <stdarg.h>

IDebugUtil& IDebugUtil::GetInstance()
{
	static DebugUtil_Win32_Impl s_DebugUtil_Win32_Impl;
	return s_DebugUtil_Win32_Impl;
}

DebugUtil_Win32_Impl::DebugUtil_Win32_Impl()
{
	m_pLogFile = NULL;
	m_hConsole = NULL;
}

DebugUtil_Win32_Impl::~DebugUtil_Win32_Impl()
{
	// TODO: 
}

bool DebugUtil_Win32_Impl::Initialize()
{
	fopen_s(&m_pLogFile, "log.txt", "w");
	if (!m_pLogFile) return false;

	AllocConsole();
	m_hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		// return an OS file handle

	return true;
}

void DebugUtil_Win32_Impl::Terminate()
{
	if (m_pLogFile)
	{
		fclose(m_pLogFile);
		m_pLogFile = NULL;
	}

	FreeConsole(); 
}

void DebugUtil_Win32_Impl::Debug(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	va_end(marker);

	OutputLog("DEBUG: ", szOut);
}

void DebugUtil_Win32_Impl::Info(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	va_end(marker);

	OutputLog("INFO: ", szOut);
}

void DebugUtil_Win32_Impl::Error(const char* format, ...)
{
	va_list marker;
	va_start(marker, format);

	char szOut[MAX_BUFFER_SIZE];
	vsprintf_s(szOut, MAX_BUFFER_SIZE, format, marker);
	va_end(marker);

	OutputLog("ERROR: ", szOut);
}

void DebugUtil_Win32_Impl::OutputLog(const char* pszTag, const char* pszLog)
{
	fputs(pszTag, m_pLogFile);
	fputs(pszLog, m_pLogFile);
	fputs("\n", m_pLogFile);

	DWORD dwBytesWrite = 0;
	WriteFile(m_hConsole, pszTag, strlen(pszTag), &dwBytesWrite, NULL);
	WriteFile(m_hConsole, pszLog, strlen(pszLog), &dwBytesWrite, NULL);
	WriteFile(m_hConsole, "\n", strlen("\n"), &dwBytesWrite, NULL);
}
