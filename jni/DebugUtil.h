/*!
 * \file DebugUtil.h
 * \date 7-19-2011 11:27:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __DEBUGUTIL_H__
#define __DEBUGUTIL_H__
#include <android/log.h>

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "spank", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "spank", __VA_ARGS__))

#endif // __DEBUGUTIL_H__