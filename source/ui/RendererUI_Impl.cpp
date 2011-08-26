/*!
 * \file RendererUI_Impl.cpp
 * \date 8-23-2011 17:33:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "RendererUI_Impl.h"
#include <IShaderMgr.h>
#include <util/StringUtil.h>
#include <util/IDebugUtil.h>
#include <util/ScreenUtil.h>
#include <IRenderer2D.h>
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>

IRendererUI& IRendererUI::GetInstance()
{
	static RendererUI_Impl s_RendererUI_Impl;
	return s_RendererUI_Impl;
}

RendererUI_Impl::RendererUI_Impl()
{
	StringUtil::ZeroMemory(m_pCaches_POS_RGB, sizeof(m_pCaches_POS_RGB));
	m_pShader_POS_RGB = NULL;

	StringUtil::ZeroMemory(m_pCaches_POS_UV, sizeof(m_pCaches_POS_UV));
	m_pShader_POS_UV = NULL;

	m_pTexture = NULL;
	m_vColor = IMath::VEC4_ONE;
	m_bRenderBegan = false;
}

RendererUI_Impl::~RendererUI_Impl()
{
	// TODO: 
}

bool RendererUI_Impl::Initialize()
{
	m_pShader_POS_RGB = IShaderMgr::GetInstance().CreateShader("line_shader.xml");
	if (!m_pShader_POS_RGB) return false;

	for (int i = 0; i < NUM_POS_RGB_CACHE; ++i)
	{
		int nVertexAttributeSize = m_pShader_POS_RGB->GetVertexAttribute()->GetStride();
		m_pCaches_POS_RGB[i] = new VertexCache(4*NUM_POS_RGB_PRIMETIVE_PER_CACHE*nVertexAttributeSize, 8*NUM_POS_RGB_PRIMETIVE_PER_CACHE);
		if (!m_pCaches_POS_RGB[i] || !m_pCaches_POS_RGB[i]->IsOK()) return false;
		m_pCaches_POS_RGB[i]->ConnectEvent(MI_RENDERER_UI_FLUSH, this, CAST_MSG_CALLBACK(&RendererUI_Impl::OnLineCacheFlushed));
	}

	m_pShader_POS_UV = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if (!m_pShader_POS_UV) return false;

	for (int i = 0; i < NUM_POS_UV_CACHE; ++i)
	{
		int nVertexAttributeSize = m_pShader_POS_UV->GetVertexAttribute()->GetStride();
		m_pCaches_POS_UV[i] = new VertexCache(4*NUM_POS_UV_PRIMETIVE_PER_CACHE*nVertexAttributeSize, 6*NUM_POS_UV_PRIMETIVE_PER_CACHE);
		if (!m_pCaches_POS_UV[i] || !m_pCaches_POS_UV[i]->IsOK()) return false;
		m_pCaches_POS_UV[i]->ConnectEvent(MI_RENDERER_UI_FLUSH, this, CAST_MSG_CALLBACK(&RendererUI_Impl::OnTriangleCacheFlushed));
	}

	return true;
}

void RendererUI_Impl::Terminate()
{
	for (int i = 0; i < NUM_POS_RGB_CACHE; ++i)
	{
		SAFE_DELETE(m_pCaches_POS_RGB[i]);
	}
	SAFE_RELEASE(m_pShader_POS_RGB);

	for (int i = 0; i < NUM_POS_UV_CACHE; ++i)
	{
		SAFE_DELETE(m_pCaches_POS_UV[i]);
	}
	SAFE_RELEASE(m_pShader_POS_UV);
}

void RendererUI_Impl::SetTexture(ITexture* pTexture)
{
	m_pTexture = pTexture;
}

void RendererUI_Impl::SetColor(float r, float g, float b, float a)
{
	m_vColor.x = r;
	m_vColor.y = g;
	m_vColor.z = b;
	m_vColor.w = a;
}

void RendererUI_Impl::DrawLineList(const VATTR_POS_RGB* pVerts, uint nVerts, const ushort* pIndis, uint nIndis)
{
	AddPrimetive(m_pCaches_POS_RGB, NUM_POS_RGB_CACHE, m_pShader_POS_RGB, pVerts, nVerts, pIndis, nIndis);
}

void RendererUI_Impl::DrawLineRect(const QUAD_VERT_POS_RGB& quad)
{
	static const ushort s_Indis[8] = {0, 1, 1, 3, 3, 2, 2, 0};
	AddPrimetive(m_pCaches_POS_RGB, NUM_POS_RGB_CACHE, m_pShader_POS_RGB, &quad.verts[0], 4, s_Indis, 8);
}

void RendererUI_Impl::DrawLineRect(const Vector2& pos, const Vector2& size)
{
	DrawLineRect(pos.x, pos.y, size.x, size.y);
}

void RendererUI_Impl::DrawLineRect(float x, float y, float width, float height)
{
	static QUAD_VERT_POS_RGB s_quad;

	s_quad.verts[0].x = x;
	s_quad.verts[0].y = y + height;
	s_quad.verts[0].z = 0.0f;
	s_quad.verts[0].r = m_vColor.x;
	s_quad.verts[0].g = m_vColor.y;
	s_quad.verts[0].b = m_vColor.z;

	s_quad.verts[1].x = x;
	s_quad.verts[1].y = y;
	s_quad.verts[1].z = 0.0f;
	s_quad.verts[1].r = m_vColor.x;
	s_quad.verts[1].g = m_vColor.y;
	s_quad.verts[1].b = m_vColor.z;

	s_quad.verts[2].x = x + width;
	s_quad.verts[2].y = y + height;
	s_quad.verts[2].z = 0.0f;
	s_quad.verts[2].r = m_vColor.x;
	s_quad.verts[2].g = m_vColor.y;
	s_quad.verts[2].b = m_vColor.z;

	s_quad.verts[3].x = x + width;
	s_quad.verts[3].y = y;
	s_quad.verts[3].z = 0.0f;
	s_quad.verts[3].r = m_vColor.x;
	s_quad.verts[3].g = m_vColor.y;
	s_quad.verts[3].b = m_vColor.z;

	DrawLineRect(s_quad);
}

void RendererUI_Impl::DrawTriangleList(const VATTR_POS_UV* pVerts, uint nVerts, const ushort* pIndis, uint nIndis)
{
	AddPrimetive(m_pCaches_POS_UV, NUM_POS_UV_CACHE, m_pShader_POS_UV, pVerts, nVerts, pIndis, nIndis);
}

void RendererUI_Impl::DrawTriangleRect(const QUAD_VERT_POS_UV& quad)
{
	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};
	AddPrimetive(m_pCaches_POS_UV, NUM_POS_UV_CACHE, m_pShader_POS_UV, &quad.verts[0], 4, s_Indis, 6);
}

void RendererUI_Impl::BeginRender()
{
	if (m_bRenderBegan) return;

	m_bRenderBegan = true;
	m_pTexture = NULL;

	// set transform matrix for ui
	const Vector2& halfScreenSize = ScreenUtil::GetInstance().GetHalfScreenSize();
	Matrix4x4 matModelView;
	IMath::BuildTranslateMatrix(matModelView, -halfScreenSize.x, halfScreenSize.y, 0.0f);
	matModelView.e[Matrix4x4::E22] = -1.0f;
	IRenderer2D::GetInstance().SetModelViewMatrix(matModelView);
}

void RendererUI_Impl::EndRender()
{
	if (!m_bRenderBegan) return;

	for (int i = 0; i < NUM_POS_RGB_CACHE; ++i)
	{
		m_pCaches_POS_RGB[i]->Flush();
		m_pCaches_POS_RGB[i]->SetShader(NULL);
		m_pCaches_POS_RGB[i]->SetTexture(NULL);
	}

	for (int i = 0; i < NUM_POS_UV_CACHE; ++i)
	{
		m_pCaches_POS_UV[i]->Flush();
		m_pCaches_POS_UV[i]->SetShader(NULL);
		m_pCaches_POS_UV[i]->SetTexture(NULL);
	}

	m_pShader_POS_RGB->Reset();
	m_pShader_POS_UV->Reset();

	m_pTexture = NULL;
	m_bRenderBegan = false;
}

bool RendererUI_Impl::AddPrimetive(VertexCache** pCache, int nNumCache, IShader* pShader, const void* pVerts, uint nVerts, const ushort* pIndis, uint nIndis)
{
	if (!m_bRenderBegan) return false;

	VertexCache* pEmptyCache = NULL;
	VertexCache* pMatchCache = NULL;

	for (int i = 0; i < nNumCache; ++i)
	{
		if (pCache[i]->GetShader() == pShader
			&& pCache[i]->GetTexture() == m_pTexture)
		{
			pMatchCache = pCache[i];
			break;
		}

		if (!pEmptyCache && pCache[i]->GetNumVerts() == 0)
		{
			pEmptyCache = pCache[i];
		}
	}

	if (pMatchCache)
	{
		if (!pMatchCache->AddVerts(pVerts, nVerts, pIndis, nIndis))
		{
			pMatchCache->Flush();
			bool bOK = pMatchCache->AddVerts(pVerts, nVerts, pIndis, nIndis);
			if (!bOK)
			{
				LOGE("IRendererUI AddPrimetive Failed with nVerts:%d, nIndis:%d", nVerts, nIndis);
				return false;
			}
		}
	}
	else if (pEmptyCache)
	{
		pEmptyCache->SetTexture(m_pTexture);
		pEmptyCache->SetShader(pShader);
		bool bOK = pEmptyCache->AddVerts(pVerts, nVerts, pIndis, nIndis);
		if (!bOK)
		{
			LOGE("IRendererUI AddPrimetive Failed with nVerts:%d, nIndis:%d", nVerts, nIndis);
			return false;
		}
	}
	else
	{
		LOGE("IRendererUI no more valid vertex cache");
		return false;
	}

	return true;
}

bool RendererUI_Impl::OnLineCacheFlushed(IMsgBase* pMsg)
{
	MsgCommon* pMsgFlush = (MsgCommon*)pMsg;

	VertexCache* pCache = (VertexCache*)pMsgFlush->GetObject();
	if (!pCache) return false;

	IShader* pShader = pCache->GetShader();
	pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	IRenderer2D::GetInstance().DrawLineList(pCache->GetVerts(), pCache->GetNumVerts(), pCache->GetIndis(), pCache->GetNumIndis(), pShader);
	return true;
}

bool RendererUI_Impl::OnTriangleCacheFlushed(IMsgBase* pMsg)
{
	MsgCommon* pMsgFlush = (MsgCommon*)pMsg;

	VertexCache* pCache = (VertexCache*)pMsgFlush->GetObject();
	if (!pCache) return false;

	ITexture* pTexture = pCache->GetTexture();
	IShader* pShader = pCache->GetShader();

	if (pTexture) pShader->SetTexture("u_texture", pTexture);
	pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());

	IRenderer2D::GetInstance().DrawTriangleList(pCache->GetVerts(), pCache->GetNumVerts(), pCache->GetIndis(), pCache->GetNumIndis(), pShader);
	return true;
}
