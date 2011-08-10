/*!
 * \file AndroidMain.cpp
 * \date 24-07-2011 15:44:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "AndroidMain.h"
#include <ICore.h>
#include <IConfig.h>
#include <InputMgr.h>
#include <IRenderDevice.h>
#include <time.h>

static uint g_nCurrTime = 0;
static uint g_nPrevTime = 0;

static uint GetCurrTime()
{
	struct timespec now;
	clock_gettime(CLOCK_MONOTONIC, &now);
	return now.tv_sec*1000 + now.tv_nsec/1000000;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_setPackagePath(JNIEnv* env, jclass cls, jstring path)
{
	jboolean isCopy = JNI_FALSE;
	const char* pszPath = env->GetStringUTFChars(path, &isCopy);
	if (isCopy == JNI_TRUE)
	{
		IConfig::GetInstance().AddString("ANDROID_RESOURCE_PACKAGE", pszPath);
		IConfig::GetInstance().AddString("RESOURCE_DIR", "assets/");
		env->ReleaseStringUTFChars(path, pszPath);
	}
}

JNIEXPORT jboolean JNICALL Java_com_zjhlogo_spank_SpankLibrary_initialize(JNIEnv* env, jclass cls, jint width, jint height)
{
	IConfig::GetInstance().AddInt("SURFACE_WIDTH", width);
	IConfig::GetInstance().AddInt("SURFACE_HEIGHT", height);
	if (!ICore::GetInstance().Initialize()) return JNI_FALSE;

	g_nCurrTime = GetCurrTime();
	g_nPrevTime = g_nCurrTime;
	return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_terminate(JNIEnv* env, jclass cls)
{
	ICore::GetInstance().Terminate();
}


JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_step(JNIEnv* env, jclass cls)
{
	g_nCurrTime = GetCurrTime();
	ICore::GetInstance().Update((g_nCurrTime - g_nPrevTime)/1000.0f);

	ICore::GetInstance().PreRender();
	ICore::GetInstance().Render();
	ICore::GetInstance().PostRender();

	g_nPrevTime = g_nCurrTime;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchBegin(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	float fx = x - IRenderDevice::GetInstance().GetSurfaceWidth() / 2.0f;
	float fy = IRenderDevice::GetInstance().GetSurfaceHeight() / 2.0f - y;
	InputMgr::GetInstance().OnTouchStart(index, fx, fy);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchMove(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	float fx = x - IRenderDevice::GetInstance().GetSurfaceWidth() / 2.0f;
	float fy = IRenderDevice::GetInstance().GetSurfaceHeight() / 2.0f - y;
	InputMgr::GetInstance().OnTouchMove(index, fx, fy);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchEnd(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	float fx = x - IRenderDevice::GetInstance().GetSurfaceWidth() / 2.0f;
	float fy = IRenderDevice::GetInstance().GetSurfaceHeight() / 2.0f - y;
	InputMgr::GetInstance().OnTouchEnd(index, fx, fy);
}
