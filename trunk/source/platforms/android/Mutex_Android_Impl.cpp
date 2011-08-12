/*!
 * \file Mutex_Android_Impl.cpp
 * \date 8-10-2011 10:29:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Mutex_Android_Impl.h"

IMutex* IMutex::CreateMutexObject()
{
	return new Mutex_Android_Impl();
}

Mutex_Android_Impl::Mutex_Android_Impl()
{
	pthread_mutex_init(&m_Mutex, NULL);
}

Mutex_Android_Impl::~Mutex_Android_Impl()
{
	pthread_mutex_destroy(&m_Mutex);
}

void Mutex_Android_Impl::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}

void Mutex_Android_Impl::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}
