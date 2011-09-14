/*!
 * \file Mutex_Android_Impl.h
 * \date 8-10-2011 10:27:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MUTEX_ANDROID_IMPL_H__
#define __MUTEX_ANDROID_IMPL_H__

#include <IMutex.h>
#include <pthread.h>

class Mutex_Android_Impl : public IMutex
{
public:
	DECLARE_RTTI(Mutex_Android_Impl, IMutex);

	Mutex_Android_Impl();
	virtual ~Mutex_Android_Impl();

	virtual void Lock();
	virtual void Unlock();

private:
	pthread_mutex_t m_Mutex;

};
#endif // __MUTEX_ANDROID_IMPL_H__
