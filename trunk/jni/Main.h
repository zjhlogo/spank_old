/*!
 * \file Main.h
 * \date 17-05-2011 21:06:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#include <android/native_activity.h>
#include <android/log.h>

#ifdef __cplusplus
extern "C" {
#endif

#define LOGI(...) ((void)__android_log_print(ANDROID_LOG_INFO, "coldblood", __VA_ARGS__))
#define LOGE(...) ((void)__android_log_print(ANDROID_LOG_ERROR, "coldblood", __VA_ARGS__))

void OnDestroy(ANativeActivity* activity);
void OnStart(ANativeActivity* activity);
void OnResume(ANativeActivity* activity);
void* OnSaveInstanceState(ANativeActivity* activity, size_t* outLen);
void OnPause(ANativeActivity* activity);
void OnStop(ANativeActivity* activity);
void OnConfigurationChanged(ANativeActivity* activity);
void OnLowMemory(ANativeActivity* activity);
void OnWindowFocusChanged(ANativeActivity* activity, int focused);
void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window);
void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window);
void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue);
void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue);
void* MainLoop(void* pParam);

#ifdef __cplusplus
}
#endif

#endif // __MAIN_H__
