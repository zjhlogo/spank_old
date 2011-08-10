/*!
 * \file Mutex_Impl.cpp
 * \date 8-10-2011 10:29:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Mutex_Impl.h"

IMutex* IMutex::CreateMutexObject()
{
	return new Mutex_Impl();
}

Mutex_Impl::Mutex_Impl()
{
	InitializeCriticalSection(&m_CriticalSection);
}

Mutex_Impl::~Mutex_Impl()
{
	DeleteCriticalSection(&m_CriticalSection);
}

void Mutex_Impl::Lock()
{
	EnterCriticalSection(&m_CriticalSection);
}

void Mutex_Impl::Unlock()
{
	LeaveCriticalSection(&m_CriticalSection);
}
