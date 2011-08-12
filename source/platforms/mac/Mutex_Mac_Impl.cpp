/*!
 * \file Mutex_Mac_Impl.cpp
 * \date 7-28-2011 17:46:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Mutex_Mac_Impl.h"

IMutex* IMutex::CreateMutexObject()
{
	return new Mutex_Mac_Impl();
}

Mutex_Mac_Impl::Mutex_Mac_Impl()
{
	pthread_mutex_init(&m_Mutex, NULL);
}

Mutex_Mac_Impl::~Mutex_Mac_Impl()
{
	pthread_mutex_destroy(&m_Mutex);
}

void Mutex_Mac_Impl::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}

void Mutex_Mac_Impl::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}
