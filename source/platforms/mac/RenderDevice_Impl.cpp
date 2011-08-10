/*!
 * \file RenderDevice_Impl.cpp
 * \date 23-07-2011 10:33:14
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RenderDevice_Impl.h"
#include <IConfig.h>
#include <OpenGLES/ES2/glext.h>
#include <OpenGLES/ES2/gl.h>

IRenderDevice& IRenderDevice::GetInstance()
{
	static RenderDevice_Impl s_RenderDevice_Impl;
	return s_RenderDevice_Impl;
}

RenderDevice_Impl::RenderDevice_Impl()
{
	m_nSurfaceWidth = 0;
	m_nSurfaceHeight = 0;
}

RenderDevice_Impl::~RenderDevice_Impl()
{
	// TODO:
}

bool RenderDevice_Impl::Initialize()
{
	m_nSurfaceWidth = IConfig::GetInstance().GetInt("SURFACE_WIDTH");
	m_nSurfaceHeight = IConfig::GetInstance().GetInt("SURFACE_HEIGHT");
	if (m_nSurfaceWidth <= 0 || m_nSurfaceHeight <= 0) return false;

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);
	
	glEnable(GL_TEXTURE_2D);
	
	glViewport(0, 0, m_nSurfaceWidth, m_nSurfaceHeight);
	return true;
}

void RenderDevice_Impl::Terminate()
{
	// TODO: 
}

int RenderDevice_Impl::GetSurfaceWidth() const
{
	return m_nSurfaceWidth;
}

int RenderDevice_Impl::GetSurfaceHeight() const
{
	return m_nSurfaceHeight;
}

void RenderDevice_Impl::BeginRender()
{
	glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// TODO: clear up render state
}

void RenderDevice_Impl::EndRender()
{
	glFlush();
}