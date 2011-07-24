/*!
 * \file RenderDevice_Impl.cpp
 * \date 23-07-2011 12:43:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Impl.h"
#include <GLES2/gl2.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Impl s_RenderDevice_Impl;
	return s_RenderDevice_Impl;
}

bool RenderDevice_Impl::Initialize()
{
	return true;
}

void RenderDevice_Impl::Terminate()
{
	// TODO: 
}

void RenderDevice_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}

void RenderDevice_Impl::EndRender()
{
	// TODO: 
}
