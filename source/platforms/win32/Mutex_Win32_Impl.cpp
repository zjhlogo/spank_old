/*!
 * \file Mutex_Impl.cpp
 * \date 8-10-2011 10:29:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Mutex_Win32_Impl.h"

IMutex* IMutex::CreateMutexObject()
{
	return new Mutex_Win32_Impl();
}

Mutex_Win32_Impl::Mutex_Win32_Impl()
{
	InitializeCriticalSection(&m_CriticalSection);
}

Mutex_Win32_Impl::~Mutex_Win32_Impl()
{
	DeleteCriticalSection(&m_CriticalSection);
}

void Mutex_Win32_Impl::Lock()
{
	EnterCriticalSection(&m_CriticalSection);
}

void Mutex_Win32_Impl::Unlock()
{
	LeaveCriticalSection(&m_CriticalSection);
}
