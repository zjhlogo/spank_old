/*!
 * \file DebugUtil_Android_Impl.h
 * \date 7-20-2011 18:06:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DEBUGUTIL_ANDROID_IMPL_H__
#define __DEBUGUTIL_ANDROID_IMPL_H__

#include <util/IDebugUtil.h>

class DebugUtil_Android_Impl : public IDebugUtil
{
public:
	DebugUtil_Android_Impl();
	virtual ~DebugUtil_Android_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Debug(const char* format, ...);
	virtual void Info(const char* format, ...);
	virtual void Error(const char* format, ...);

};

#endif // __DEBUGUTIL_ANDROID_IMPL_H__
