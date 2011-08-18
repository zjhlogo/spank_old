/*!
 * \file AndroidMain.cpp
 * \date 24-07-2011 15:44:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "AndroidMain.h"
#include <ICore.h>
#include <util/ConfigUtil.h>
#include <util/ScreenUtil.h>
#include <util/IDebugUtil.h>
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
		ConfigUtil::GetInstance().AddString("ANDROID_RESOURCE_PACKAGE", pszPath);
		ConfigUtil::GetInstance().AddString("RESOURCE_DIR", "assets/");
		env->ReleaseStringUTFChars(path, pszPath);
	}
}

JNIEXPORT jboolean JNICALL Java_com_zjhlogo_spank_SpankLibrary_initialize(JNIEnv* env, jclass cls, jint width, jint height)
{
	ConfigUtil::GetInstance().AddInt("SURFACE_WIDTH", width);
	ConfigUtil::GetInstance().AddInt("SURFACE_HEIGHT", height);

	if (!ICore::GetInstance().Initialize())
	{
		LOGD("initialize failed with surface size %dx%d", width, height);
		return JNI_FALSE;
	}

	LOGD("initialize ok, surface size %dx%d", width, height);
	g_nCurrTime = GetCurrTime();
	g_nPrevTime = g_nCurrTime;
	return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_terminate(JNIEnv* env, jclass cls)
{
	LOGD("spank terminated");
	ICore::GetInstance().Terminate();

	// force exist the program
	int* pNull = NULL;
	*pNull = 8888;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_step(JNIEnv* env, jclass cls)
{
	g_nCurrTime = GetCurrTime();

	ICore::GetInstance().Update((g_nCurrTime - g_nPrevTime)/1000.0f);
	ICore::GetInstance().Render();

	g_nPrevTime = g_nCurrTime;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchBegin(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, x, y);
	InputMgr::GetInstance().OnTouchStart(index, vPos.x, vPos.y);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchMove(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, x, y);
	InputMgr::GetInstance().OnTouchMove(index, vPos.x, vPos.y);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_touchEnd(JNIEnv* env, jclass cls, jint index, jfloat x, jfloat y)
{
	Vector2 vPos;
	ScreenUtil::GetInstance().DevicePointToScreen(vPos, x, y);
	InputMgr::GetInstance().OnTouchEnd(index, vPos.x, vPos.y);
}
