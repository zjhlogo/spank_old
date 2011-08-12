/*!
 * \file RenderDevice_Mac_Impl.cpp
 * \date 23-07-2011 10:33:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Mac_Impl.h"
#include <util/ConfigUtil.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES2/gl.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Mac_Impl s_RenderDevice_Mac_Impl;
	return s_RenderDevice_Mac_Impl;
}

RenderDevice_Mac_Impl::RenderDevice_Mac_Impl()
{
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;
}

RenderDevice_Mac_Impl::~RenderDevice_Mac_Impl()
{
	// TODO:
}

bool RenderDevice_Mac_Impl::Initialize()
{
	m_nSurfaceWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
	m_nSurfaceHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
	if (m_nSurfaceWidth <= 0 || m_nSurfaceHeight <= 0) return false;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	
	glViewport(0, 0, m_nSurfaceWidth, m_nSurfaceHeight);
	
	return true;
}

void RenderDevice_Mac_Impl::Terminate()
{
	// TODO: 
}

int RenderDevice_Mac_Impl::GetSurfaceWidth() const
{
	return m_nSurfaceWidth;
}

int RenderDevice_Mac_Impl::GetSurfaceHeight() const
{
	return m_nSurfaceHeight;
}

void RenderDevice_Mac_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// TODO: clear up render state
}

void RenderDevice_Mac_Impl::EndRender()
{
	glFlush();
}
