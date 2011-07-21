/*!
 * \file IDebugUtil.h
 * \date 7-20-2011 16:40:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IDEBUGUTIL_H__
#define __IDEBUGUTIL_H__

class IDebugUtil
{
public:
	static IDebugUtil& GetInstance();

	virtual void Debug(const char* format, ...) = 0;
	virtual void Info(const char* format, ...) = 0;
	virtual void Error(const char* format, ...) = 0;
};

#ifdef DEBUG_OUT
	#define LOGD(...) ((void)IDebugUtil::GetInstance().Debug(__VA_ARGS__))
	#define LOGI(...) ((void)IDebugUtil::GetInstance().Info(__VA_ARGS__))
	#define LOGE(...) ((void)IDebugUtil::GetInstance().Error(__VA_ARGS__))
#else
	#define LOGD(...) (0)
	#define LOGI(...) (0)
	#define LOGE(...) (0)
#endif

#endif // __IDEBUGUTIL_H__