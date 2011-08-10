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
	pthread_mutex_init(&m_Mutex, NULL);
}

Mutex_Impl::~Mutex_Impl()
{
	pthread_mutex_destroy(&m_Mutex);
}

void Mutex_Impl::Lock()
{
	pthread_mutex_lock(&m_Mutex);
}

void Mutex_Impl::Unlock()
{
	pthread_mutex_unlock(&m_Mutex);
}
