/*!
 * \file UIString.cpp
 * \date 8-22-2011 15:43:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/UIString.h>
#include <util/StringUtil.h>

UIString::UIString(IFont* pFont)
{
	m_pFont = pFont;
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
	// TODO: 
}

bool UIString::SetText(const char* pszText)
{
	if (!pszText)
	{
		// TODO: clear char caches
		m_strText.clear();
		m_UnicodeChars.clear();
		m_nCharCount = 0;
		return true;
	}

	m_strText = pszText;
	m_nCharCount = StringUtil::Utf8ToUnicode(NULL, 0, pszText);
	m_UnicodeChars.resize(m_nCharCount+1);
	// TODO: recreate char cache
	return true;
}

const char* UIString::GetText()
{
	return m_strText.c_str();
}

bool UIString::CreateCharVerts()
{
	// TODO: 
	return true;
}

void UIString::ClearCharVerts()
{
	// TODO: 
}

void UIString::SetPosition(const Vector2& pos)
{
	m_vPosition = pos;
}

const Vector2& UIString::GetPosition() const
{
	return m_vPosition;
}
