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

IRendererUI& IRendererUI::GetInstance()
{
	static RendererUI_Impl s_RendererUI_Impl;
	return s_RendererUI_Impl;
}

RendererUI_Impl::RendererUI_Impl()
{
	m_pTexture = NULL;
	m_pShader = NULL;
	m_bRenderBegan = false;
	StringUtil::ZeroMemory(m_pVertexCaches, sizeof(m_pVertexCaches));
}

RendererUI_Impl::~RendererUI_Impl()
{
	// TODO: 
}

bool RendererUI_Impl::Initialize()
{
	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if (!m_pShader) return false;

	for (int i = 0; i < NUM_CACHES; ++i)
	{
		m_pVertexCaches[i] = new VertexCache(VERTS_CACHE_SIZE, INDIS_CACHE_SIZE);
		if (!m_pVertexCaches[i] || !m_pVertexCaches[i]->IsOK()) return false;
	}

	return true;
}

void RendererUI_Impl::Terminate()
{
	for (int i = 0; i < NUM_CACHES; ++i)
	{
		SAFE_DELETE(m_pVertexCaches[i]);
	}

	SAFE_RELEASE(m_pShader);
}

void RendererUI_Impl::SetTexture(ITexture* pTexture)
{
	m_pTexture = pTexture;
}

void RendererUI_Impl::DrawTriangleList(const void* pVerts, uint nVerts, const ushort* pIndis, uint nIndis)
{
	if (!m_bRenderBegan) return;

	VertexCache* pEmptyCache = NULL;
	VertexCache* pMatchCache = NULL;

	for (int i = 0; i < NUM_CACHES; ++i)
	{
		if (m_pVertexCaches[i]->Compare(m_pTexture, m_pShader))
		{
			pMatchCache = m_pVertexCaches[i];
			break;
		}

		if (!pEmptyCache && m_pVertexCaches[i]->GetVertsCount() == 0)
		{
			pEmptyCache = m_pVertexCaches[i];
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
				LOGE("IRendererUI AddVerts Failed with nVerts:%d, nIndis:%d", nVerts, nIndis);
			}
		}
	}
	else if (pEmptyCache)
	{
		pEmptyCache->SetTexture(m_pTexture);
		pEmptyCache->SetShader(m_pShader);
		bool bOK = pEmptyCache->AddVerts(pVerts, nVerts, pIndis, nIndis);
		if (!bOK)
		{
			LOGE("IRendererUI AddVerts Failed with nVerts:%d, nIndis:%d", nVerts, nIndis);
		}
	}
	else
	{
		LOGE("IRendererUI no more valid vertex cache");
	}
}

void RendererUI_Impl::DrawRect(const QUAD_VERT_POS_UV& quadVerts)
{
	static const ushort s_Indis[6] = {0, 1, 2, 1, 3, 2};
	DrawTriangleList(&quadVerts.verts[0], 4, s_Indis, 6);
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

	for (int i = 0; i < NUM_CACHES; ++i)
	{
		m_pVertexCaches[i]->Flush();
		m_pVertexCaches[i]->SetTexture(NULL);
	}

	m_pTexture = NULL;
	m_bRenderBegan = false;
}
