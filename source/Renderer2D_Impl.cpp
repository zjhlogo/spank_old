/*!
 * \file Renderer2D_Impl.cpp
 * \date 7-25-2011 10:45:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Renderer2D_Impl.h"
#include <IRenderDevice.h>
#include <IShaderMgr.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <GLES2/gl2.h>
#include <math.h>

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
	IMath::BuildIdentityMatrix(m_matModelView);
	IMath::BuildIdentityMatrix(m_matProj);

	float fSurfaceWidth = (float)IRenderDevice::GetInstance().GetSurfaceWidth();
	float fSurfaceHeight = (float)IRenderDevice::GetInstance().GetSurfaceHeight();
	IMath::BuildOrthoMatrix(m_matProj, -fSurfaceWidth/2.0f, fSurfaceWidth/2.0f, -fSurfaceHeight/2.0f, fSurfaceHeight/2.0f, 0.1f, 1000.0f);

	float fDegree = ScreenUtil::GetInstance().GetRotationDegree();
	if (fabsf(fDegree - 0.0f) > IMath::FLOAT_MIN)
	{
		// setup the rotation matrix to rotate world
		Matrix4x4 matRot;
		IMath::BuildRotateMatrixZ(matRot, IMath::ToRadian(fDegree));
		m_matProj *= matRot;
	}

	return true;
}

void Renderer2D_Impl::Terminate()
{
	// TODO: 
}

void Renderer2D_Impl::SetModelViewMatrix(const Matrix4x4& mat)
{
	m_matModelView = mat;
}

const Matrix4x4& Renderer2D_Impl::GetModelViewMatrix() const
{
	return m_matModelView;
}

void Renderer2D_Impl::SetProjectionMatrix(const Matrix4x4& mat)
{
	m_matProj = mat;
}

const Matrix4x4& Renderer2D_Impl::GetProjectionMatrix() const
{
	return m_matProj;
}

void Renderer2D_Impl::SetShader(IShader* pShader)
{
	m_pShader = pShader;
}

IShader* Renderer2D_Impl::GetShader()
{
	return m_pShader;
}

void Renderer2D_Impl::BeginRender2D()
{
	if (!m_pShader) return;

	m_pShader->Reset();
}

void Renderer2D_Impl::EndRender2D()
{
	// TODO: 
}

void Renderer2D_Impl::DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis)
{
	if (!m_pShader) return;

	Matrix4x4 matModelViewProj = m_matProj*m_matModelView;
	matModelViewProj.Transport();
	m_pShader->SetMatrix4x4("u_matModelViewProj", &matModelViewProj);

	m_pShader->Commit(pVerts);
	glDrawElements(GL_TRIANGLES, nNumIndis, GL_UNSIGNED_SHORT, pIndis);
}

void Renderer2D_Impl::DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis)
{
	if (!m_pShader) return;

	Matrix4x4 matModelViewProj = m_matProj*m_matModelView;
	matModelViewProj.Transport();
	m_pShader->SetMatrix4x4("u_matModelViewProj", &matModelViewProj);

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

	if (!m_pShader) return;

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

void Renderer2D_Impl::DrawRect(const void* pVerts)
{
	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};

	if (!m_pShader) return;

	DrawTriangleList(pVerts, 4, s_Indis, 6);
}
