/*!
 * \file UIString.cpp
 * \date 8-22-2011 15:43:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIString.h>
#include <util/StringUtil.h>
#include <ui/IRendererUI.h>
#include <ui/IFontMgr.h>

UIString::UIString(IFont* pFont, const char* pszText)
{
	m_pFont = pFont;
	SetText(pszText);
}

UIString::UIString(const char* pszText)
{
	m_pFont = IFontMgr::GetInstance().GetDefaultFont();
	SetText(pszText);
}

UIString::~UIString()
{
	// do not release m_pFont
	ClearCharVerts();
}

void UIString::Update(float dt)
{
	// TODO: 
}

void UIString::Render(const Vector2& pos)
{
	float fBasePosX = pos.x;
	float fBasePosY = pos.y;

	for (TV_CHAR_INFO::const_iterator it = m_vCharInfo.begin(); it != m_vCharInfo.end(); ++it)
	{
		const IFont::CHAR_INFO* pCharInfo = (*it);

		QUAD_VERT_POS_UV quad;

		float fCharPosX = fBasePosX + pCharInfo->offsetx;
		float fCharPosY = fBasePosY + pCharInfo->offsety;

		quad.verts[0].x = fCharPosX;
		quad.verts[0].y = fCharPosY + pCharInfo->height;
		quad.verts[0].z = 0.0f;
		quad.verts[0].u = pCharInfo->u;
		quad.verts[0].v = pCharInfo->v;

		quad.verts[1].x = fCharPosX;
		quad.verts[1].y = fCharPosY;
		quad.verts[1].z = 0.0f;
		quad.verts[1].u = pCharInfo->u;
		quad.verts[1].v = pCharInfo->v+pCharInfo->dv;

		quad.verts[2].x = fCharPosX + pCharInfo->width;
		quad.verts[2].y = fCharPosY + pCharInfo->height;
		quad.verts[2].z = 0.0f;
		quad.verts[2].u = pCharInfo->u+pCharInfo->du;
		quad.verts[2].v = pCharInfo->v;

		quad.verts[3].x = fCharPosX + pCharInfo->width;
		quad.verts[3].y = fCharPosY;
		quad.verts[3].z = 0.0f;
		quad.verts[3].u = pCharInfo->u+pCharInfo->du;
		quad.verts[3].v = pCharInfo->v+pCharInfo->dv;

		IRendererUI::GetInstance().SetTexture(pCharInfo->pTexture);
		IRendererUI::GetInstance().DrawTriangleRect(quad);

		fBasePosX += pCharInfo->advance;
	}
}

bool UIString::SetText(const char* pszText)
{
	// create char cache
	return CreateCharVerts(pszText);
}

bool UIString::CreateCharVerts(const char* pszText)
{
	ClearCharVerts();

	m_nCharCount = StringUtil::Utf8ToUnicode(NULL, 0, pszText);
	if (m_nCharCount > 0)
	{
		m_UnicodeChars.resize(m_nCharCount+1);
		m_nCharCount = StringUtil::Utf8ToUnicode(&m_UnicodeChars[0], m_nCharCount+1, pszText);
	}

	m_vCharInfo.clear();
	for (int i = 0; i < m_nCharCount; ++i)
	{
		const IFont::CHAR_INFO* pCharInfo = m_pFont->GetCharInfo(m_UnicodeChars[i]);
		if (!pCharInfo) return false;

		m_vCharInfo.push_back(pCharInfo);
	}

	return true;
}

void UIString::ClearCharVerts()
{
	m_UnicodeChars.clear();
	m_nCharCount = 0;
	m_vCharInfo.clear();
}
