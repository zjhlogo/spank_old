/*!
 * \file RendererUI_Impl.cpp
 * \date 8-23-2011 17:33:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RendererUI_Impl.h"

IRendererUI& IRendererUI::GetInstance()
{
	static RendererUI_Impl s_RendererUI_Impl;
	return s_RendererUI_Impl;
}

RendererUI_Impl::RendererUI_Impl()
{
	// TODO: 
}

RendererUI_Impl::~RendererUI_Impl()
{
	// TODO: 
}

bool RendererUI_Impl::Initialize()
{
	// TODO: 
	return true;
}

void RendererUI_Impl::Terminate()
{
	// TODO: 
}

void RendererUI_Impl::SetTexture(ITexture* pTexture)
{
	// TODO: 
}

void RendererUI_Impl::DrawRect(float x, float y, float width, float height)
{
	// TODO: 
}

void RendererUI_Impl::BeginRender()
{
	// TODO: 
}

void RendererUI_Impl::EndRender()
{
	// TODO: 
}
