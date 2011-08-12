/*!
 * \file RenderDevice_Android_Impl.cpp
 * \date 23-07-2011 12:43:58
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Android_Impl.h"
#include <util/ConfigUtil.h>
#include <GLES2/gl2.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Android_Impl s_RenderDevice_Android_Impl;
	return s_RenderDevice_Android_Impl;
}

RenderDevice_Android_Impl::RenderDevice_Android_Impl()
{
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;
}

RenderDevice_Android_Impl::~RenderDevice_Android_Impl()
{
	// TODO: 
}

bool RenderDevice_Android_Impl::Initialize()
{
	m_nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	m_nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (m_nSurfaceWidth <= 0 || m_nSurfaceHeight <= 0) return false;

	// set view port
	glViewport(0, 0, m_nSurfaceWidth, m_nSurfaceHeight);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	return true;
}

void RenderDevice_Android_Impl::Terminate()
{
	// TODO: 
}

int RenderDevice_Android_Impl::GetSurfaceWidth() const
{
	return m_nSurfaceWidth;
}

int RenderDevice_Android_Impl::GetSurfaceHeight() const
{
	return m_nSurfaceHeight;
}

void RenderDevice_Android_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void RenderDevice_Android_Impl::EndRender()
{
	// TODO: 
}
