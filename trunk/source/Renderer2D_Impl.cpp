/*!
 * \file Renderer2D_Impl.cpp
 * \date 7-25-2011 10:45:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Renderer2D_Impl.h"
#include <IShaderMgr.h>
#include <IConfig.h>
#include <IDebugUtil.h>
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
	static const IVertexAttribute::ATTRIBUTE_ITEM s_VertAttrs[] = 
	{
		{3, IVertexAttribute::AT_FLOAT, 0, "a_position"},
		{2, IVertexAttribute::AT_FLOAT, 0, "a_texCoord"},
		{0, IVertexAttribute::AT_UNKNOWN, 0, ""},
	};

	m_pShader = IShaderMgr::GetInstance().CreateShaderFromFiles("shader.vs", "shader.fs", s_VertAttrs);
	if (!m_pShader)
	{
		LOGE("load default shader failed: shader.vs, shader.fs");
		return false;
	}

	int winWidth = IConfig::GetInstance().GetInt("WINDOW_WIDTH");
	int winHeight = IConfig::GetInstance().GetInt("WINDOW_HEIGHT");
	m_matOrtho.MakeOrtho(-winWidth/2.0f, winWidth/2.0f, -winHeight/2.0f, winHeight/2.0f, 1000.0f, -1000.0f);

	return true;
}

void Renderer2D_Impl::Terminate()
{
	SAFE_RELEASE(m_pShader);
}

void Renderer2D_Impl::SetTexture(ITexture* pTexture)
{
	m_pShader->SetTexture("s_texture", pTexture);
}

void Renderer2D_Impl::BeginRender2D()
{
	m_pShader->Reset();
	m_pShader->SetMatrix4x4("u_project", &m_matOrtho);
}

void Renderer2D_Impl::EndRender2D()
{
	// TODO: 
}

void Renderer2D_Impl::DrawTriangleList(const void* pVerts, uint nNumVerts)
{
	m_pShader->Commit(pVerts);
	glDrawArrays(GL_TRIANGLES, 0, nNumVerts);
}

void Renderer2D_Impl::DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis)
{
	// TODO: 
}
