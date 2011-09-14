/*!
 * \file Mutex_Impl.h
 * \date 7-28-2011 17:46:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MUTEX_MAC_IMPL_H__
#define __MUTEX_MAC_IMPL_H__

#include <IMutex.h>
#include <pthread.h>

class Mutex_Mac_Impl : public IMutex
{
public:
	DECLARE_RTTI(Mutex_Mac_Impl, IMutex);

	Mutex_Mac_Impl();
	virtual ~Mutex_Mac_Impl();
	
	virtual void Lock();
	virtual void Unlock();
	
private:
	pthread_mutex_t m_Mutex;
	
};

#endif // __MUTEX_MAC_IMPL_H__
