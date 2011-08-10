/*!
 * \file IMutex.h
 * \date 8-10-2011 10:27:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMUTEX_H__
#define __IMUTEX_H__

#include "IObject.h"

class IMutex : public IObject
{
public:
	static IMutex* CreateMutexObject();

	virtual void Lock() = 0;
	virtual void Unlock() = 0;

};
#endif // __IMUTEX_H__
