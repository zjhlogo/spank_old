/*!
 * \file RenderDevice_Impl.cpp
 * \date 23-07-2011 12:43:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Impl.h"
#include <IConfig.h>
#include <GLES2/gl2.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Impl s_RenderDevice_Impl;
	return s_RenderDevice_Impl;
}

bool RenderDevice_Impl::Initialize()
{
	int winWidth = IConfig::GetInstance().GetInt("WINDOW_WIDTH");
	int winHeight = IConfig::GetInstance().GetInt("WINDOW_HEIGHT");
	glViewport(0, 0, winWidth, winHeight);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	return true;
}

void RenderDevice_Impl::Terminate()
{
	// TODO: 
}

void RenderDevice_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderDevice_Impl::EndRender()
{
	// TODO: 
}
