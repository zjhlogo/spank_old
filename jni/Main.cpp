/*!
 * \file Main.cpp
 * \date 17-05-2011 21:06:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Main.h"
#include "GameMain.h"
#include "MessageMgr.h"

#include "msg/MsgID.h"
#include "msg/MsgWriter.h"

#include <pthread.h>

void OnDestroy(ANativeActivity* activity)
{
	MsgWriter msgWriter(MI_AAM_DESTROY);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("Destroy: %p\n", activity);
}

void OnStart(ANativeActivity* activity)
{
	pthread_t thread = 0;
	if (pthread_create(&thread, NULL, MainLoop, NULL) != 0)
	{
		// TODO: error occur
	}

	MsgWriter msgWriter(MI_AAM_START);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("Start: %p\n", activity);
}

void OnResume(ANativeActivity* activity)
{
	MsgWriter msgWriter(MI_AAM_RESUME);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("Resume: %p\n", activity);
}

void* OnSaveInstanceState(ANativeActivity* activity, size_t* outLen)
{
	MsgWriter msgWriter(MI_AAM_SAVE_INSTANCE_STATE);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("SaveInstanceState: %p\n", activity);
	outLen = 0;
	return NULL;
}

void OnPause(ANativeActivity* activity)
{
	MsgWriter msgWriter(MI_AAM_PAUSE);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("Pause: %p\n", activity);
}

void OnStop(ANativeActivity* activity)
{
	MsgWriter msgWriter(MI_AAM_STOP);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("Stop: %p\n", activity);
}

void OnConfigurationChanged(ANativeActivity* activity)
{
	MsgWriter msgWriter(MI_AAM_CONFIGURATION_CHANGED);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("ConfigurationChanged: %p\n", activity);
}

void OnLowMemory(ANativeActivity* activity)
{
	MsgWriter msgWriter(MI_AAM_LOW_MEMORY);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("LowMemory: %p\n", activity);
}

void OnWindowFocusChanged(ANativeActivity* activity, int focused)
{
	MsgWriter msgWriter(MI_AAM_WINDOW_FOCUS_CHANGED);
	msgWriter.Write(activity);
	msgWriter.Write(focused);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("WindowFocusChanged: %p -- %d\n", activity, focused);
}

void OnNativeWindowCreated(ANativeActivity* activity, ANativeWindow* window)
{
	MsgWriter msgWriter(MI_AAM_NATIVE_WINDOW_CREATED);
	msgWriter.Write(activity);
	msgWriter.Write(window);

	int nWidth = ANativeWindow_getWidth(window);
	int nHeight = ANativeWindow_getHeight(window);
	int nFormat = ANativeWindow_getFormat(window);
	msgWriter.Write(nWidth);
	msgWriter.Write(nHeight);
	msgWriter.Write(nFormat);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("NativeWindowCreated: %p -- %p, %dx%d:%d\n", activity, window, nWidth, nHeight, nFormat);
}

void OnNativeWindowDestroyed(ANativeActivity* activity, ANativeWindow* window)
{
	MsgWriter msgWriter(MI_AAM_NATIVE_WINDOW_DESTROYED);
	msgWriter.Write(activity);
	msgWriter.Write(window);

	int nWidth = ANativeWindow_getWidth(window);
	int nHeight = ANativeWindow_getHeight(window);
	int nFormat = ANativeWindow_getFormat(window);
	msgWriter.Write(nWidth);
	msgWriter.Write(nHeight);
	msgWriter.Write(nFormat);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("NativeWindowDestroyed: %p -- %p, %dx%d:%d\n", activity, window, nWidth, nHeight, nFormat);
}

void OnInputQueueCreated(ANativeActivity* activity, AInputQueue* queue)
{
	MsgWriter msgWriter(MI_AAM_INPUT_QUEUE_CREATED);
	msgWriter.Write(activity);
	msgWriter.Write(queue);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("InputQueueCreated: %p -- %p\n", activity, queue);
}

void OnInputQueueDestroyed(ANativeActivity* activity, AInputQueue* queue)
{
	MsgWriter msgWriter(MI_AAM_INPUT_QUEUE_DESTROYED);
	msgWriter.Write(activity);
	msgWriter.Write(queue);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("InputQueueDestroyed: %p -- %p\n", activity, queue);
}

void* MainLoop(void* pParam)
{
	LOGI("Thread Begin");
	GameMain game;
	game.Run();
	LOGI("Thread Done");
}

void ANativeActivity_onCreate(ANativeActivity* activity, void* savedState, size_t savedStateSize)
{
	// initizlized MessageMgr
	MessageMgr::GetInstance().Initialize();

	MsgWriter msgWriter(MI_AAM_CREATE);
	msgWriter.Write(activity);
	MessageMgr::GetInstance().PushMessage(msgWriter);

	LOGI("Creating: %p\n", activity);
    activity->callbacks->onDestroy = OnDestroy;
    activity->callbacks->onStart = OnStart;
    activity->callbacks->onResume = OnResume;
    activity->callbacks->onSaveInstanceState = OnSaveInstanceState;
    activity->callbacks->onPause = OnPause;
    activity->callbacks->onStop = OnStop;
    activity->callbacks->onConfigurationChanged = OnConfigurationChanged;
    activity->callbacks->onLowMemory = OnLowMemory;
    activity->callbacks->onWindowFocusChanged = OnWindowFocusChanged;
    activity->callbacks->onNativeWindowCreated = OnNativeWindowCreated;
    activity->callbacks->onNativeWindowDestroyed = OnNativeWindowDestroyed;
    activity->callbacks->onInputQueueCreated = OnInputQueueCreated;
    activity->callbacks->onInputQueueDestroyed = OnInputQueueDestroyed;
}
