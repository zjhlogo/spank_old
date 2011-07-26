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
	IConfig::GetInstance().AddInt("WINDOW_WIDTH", width);
	IConfig::GetInstance().AddInt("WINDOW_HEIGHT", height);
	if (!ICore::GetInstance().Initialize()) return JNI_FALSE;
	return JNI_TRUE;
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_terminate(JNIEnv* env, jclass cls)
{
	ICore::GetInstance().Terminate();
}


JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_step(JNIEnv* env, jclass cls)
{
	ICore::GetInstance().Update(0.0f);

	ICore::GetInstance().PreRender();
	ICore::GetInstance().Render();
	ICore::GetInstance().PostRender();
}
