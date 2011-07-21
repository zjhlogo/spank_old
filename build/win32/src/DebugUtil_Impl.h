/*!
 * \file DebugUtil_Impl.h
 * \date 7-20-2011 18:06:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DEBUGUTIL_IMPL_H__
#define __DEBUGUTIL_IMPL_H__

#include <IDebugUtil.h>

class DebugUtil_Impl : public IDebugUtil
{
public:
	virtual void Debug(const char* format, ...);
	virtual void Info(const char* format, ...);
	virtual void Error(const char* format, ...);

};

#endif // __DEBUGUTIL_IMPL_H__
