/*!
 * \file Main.cpp
 * \date 17-05-2011 21:06:59
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Main.h"
#include "GameMain.h"
#include <IFileMgr.h>

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_initialize(JNIEnv* env, jclass cls, jint width, jint height)
{
	GameMain::GetInstance().Initialize(width, height);
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_setPackagePath(JNIEnv* env, jclass cls, jstring path)
{
	jboolean isCopy = JNI_FALSE;
	const char* pszPath = env->GetStringUTFChars(path, &isCopy);
	if (isCopy == JNI_TRUE)
	{
		// set the package path
		IFileMgr::GetInstance().Initialize(pszPath);
		env->ReleaseStringUTFChars(path, pszPath);
	}
}

JNIEXPORT void JNICALL Java_com_zjhlogo_spank_SpankLibrary_step(JNIEnv* env, jclass cls)
{
	GameMain::GetInstance().Render();
}
