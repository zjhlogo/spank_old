/*!
 * \file DebugUtil_Mac_Impl.h
 * \date 7-20-2011 18:06:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DEBUGUTIL_MAC_IMPL_H__
#define __DEBUGUTIL_MAC_IMPL_H__

#include <util/IDebugUtil.h>

class DebugUtil_Mac_Impl : public IDebugUtil
{
public:
	enum CONST_DEFINE
	{
		MAX_BUFFER_SIZE = 1024,
	};

public:
	DECLARE_RTTI(DebugUtil_Mac_Impl, IDebugUtil);

	DebugUtil_Mac_Impl();
	virtual ~DebugUtil_Mac_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Debug(const char* format, ...);
	virtual void Info(const char* format, ...);
	virtual void Error(const char* format, ...);

};

#endif // __DEBUGUTIL_MAC_IMPL_H__
