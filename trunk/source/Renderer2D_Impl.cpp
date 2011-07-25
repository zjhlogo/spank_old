/*!
 * \file Renderer2D_Impl.cpp
 * \date 7-25-2011 10:45:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Renderer2D_Impl.h"
#include <GLES2/gl2.h>

IRenderer2D& IRenderer2D::GetInstance()
{
	static Renderer2D_Impl s_Renderer2D_Impl;
	return s_Renderer2D_Impl;
}

Renderer2D_Impl::Renderer2D_Impl()
{
	m_pShader = NULL;
}

Renderer2D_Impl::~Renderer2D_Impl()
{
	// TODO: 
}

bool Renderer2D_Impl::Initialize()
{
	// TODO: 
	return true;
}

void Renderer2D_Impl::Terminate()
{
	// TODO: 
}

void Renderer2D_Impl::SetShader(IShader* pShader)
{
	m_pShader = pShader;
}

void Renderer2D_Impl::DrawTriangleList(const void* pVerts, uint nNumVerts)
{
	if (!m_pShader) return;
	m_pShader->Commit(pVerts);
	glDrawArrays(GL_TRIANGLES, 0, nNumVerts);
}

void Renderer2D_Impl::DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis)
{
	if (!m_pShader) return;
//	m_pShader->Commit(pVerts);
}
