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

const Matrix4x4& Renderer2D_Impl::GetProjectionMatrix() const
{
	return m_matOrtho;
}

void Renderer2D_Impl::SetMatrix(const Matrix4x4* pMat)
{
	m_pShader->SetMatrix4x4("u_project", pMat);
}

void Renderer2D_Impl::SetTexture(ITexture* pTexture)
{
	m_pShader->SetTexture("s_texture", pTexture);
}

void Renderer2D_Impl::BeginRender2D()
{
	m_pShader->Reset();
}

void Renderer2D_Impl::EndRender2D()
{
	// TODO: 
}

void Renderer2D_Impl::DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis)
{
	m_pShader->Commit(pVerts);
	glDrawElements(GL_TRIANGLES, nNumIndis, GL_UNSIGNED_SHORT, pIndis);
}

void Renderer2D_Impl::DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis)
{
	m_pShader->Commit(pVerts);
	glDrawElements(GL_TRIANGLE_STRIP, nNumIndis, GL_UNSIGNED_SHORT, pIndis);
}

void Renderer2D_Impl::DrawRect(float x, float y, float width, float height)
{
	static VERTEX_ATTRIBUTE s_Verts[4] =
	{
		{-0.5f, -0.5f, 0.0f, 0.0f, 0.0f},
		{-0.5f, +0.5f, 0.0f, 0.0f, 1.0f},
		{+0.5f, -0.5f, 0.0f, 1.0f, 0.0f},
		{+0.5f, +0.5f, 0.0f, 1.0f, 1.0f},
	};

	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};

	float halfWidth = width/2.0f;
	float halfHeight = height/2.0f;

	s_Verts[0].x = x - halfWidth;
	s_Verts[0].y = y - halfHeight;
	s_Verts[1].x = x - halfWidth;
	s_Verts[1].y = y + halfHeight;
	s_Verts[2].x = x + halfWidth;
	s_Verts[2].y = y - halfHeight;
	s_Verts[3].x = x + halfWidth;
	s_Verts[3].y = y + halfHeight;

	DrawTriangleList(s_Verts, 4, s_Indis, 6);
}
