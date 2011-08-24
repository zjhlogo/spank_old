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

UIString::UIString(IFont* pFont)
{
	m_pFont = pFont;
	m_vPosition = IMath::VEC2_ZERO;
}

UIString::~UIString()
{
	// TODO: 
}

void UIString::Update(float dt)
{
	// TODO: 
}

void UIString::Render()
{
	float fBasePosX = m_vPosition.x;
	float fBasePosY = m_vPosition.y;

	for (TV_CHAR_INFO::const_iterator it = m_vCharInfo.begin(); it != m_vCharInfo.end(); ++it)
	{
		const IFont::CHAR_INFO* pCharInfo = (*it);

		VATTR_POS_UV Verts[4];

		float fCharPosX = fBasePosX + pCharInfo->offsetx;
		float fCharPosY = fBasePosY + pCharInfo->offsety;

		Verts[0].x = fCharPosX;
		Verts[0].y = fCharPosY - pCharInfo->height;
		Verts[0].z = 0.0f;
		Verts[0].u = pCharInfo->u;
		Verts[0].v = pCharInfo->v;

		Verts[1].x = fCharPosX;
		Verts[1].y = fCharPosY;
		Verts[1].z = 0.0f;
		Verts[1].u = pCharInfo->u;
		Verts[1].v = pCharInfo->v+pCharInfo->dv;

		Verts[2].x = fCharPosX + pCharInfo->width;
		Verts[2].y = fCharPosY - pCharInfo->height;
		Verts[2].z = 0.0f;
		Verts[2].u = pCharInfo->u+pCharInfo->du;
		Verts[2].v = pCharInfo->v;

		Verts[3].x = fCharPosX + pCharInfo->width;
		Verts[3].y = fCharPosY;
		Verts[3].z = 0.0f;
		Verts[3].u = pCharInfo->u+pCharInfo->du;
		Verts[3].v = pCharInfo->v+pCharInfo->dv;

		IRendererUI::GetInstance().DrawRect(Verts);

		fBasePosX += pCharInfo->advance;
	}
}

bool UIString::SetText(const char* pszText)
{
	if (!pszText)
	{
		m_strText.clear();
		// clear char caches
		ClearCharVerts();
		return true;
	}

	m_strText = pszText;
	// create char cache
	return CreateCharVerts();
}

const char* UIString::GetText()
{
	return m_strText.c_str();
}

bool UIString::CreateCharVerts()
{
	m_nCharCount = StringUtil::Utf8ToUnicode(NULL, 0, m_strText.c_str());
	if (m_nCharCount > 0)
	{
		m_UnicodeChars.resize(m_nCharCount+1);
		m_nCharCount = StringUtil::Utf8ToUnicode(&m_UnicodeChars[0], m_nCharCount+1, m_strText.c_str());
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

void UIString::SetPosition(const Vector2& pos)
{
	m_vPosition = pos;
}

const Vector2& UIString::GetPosition() const
{
	return m_vPosition;
}
