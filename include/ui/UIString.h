/*!
 * \file UIString.h
 * \date 8-22-2011 15:43:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UISTRING_H__
#define __UISTRING_H__

#include "../IRenderableObject.h"
#include "IFont.h"
#include <string>
#include <vector>

class UIString : public IRenderableObject
{
public:
	typedef std::vector<ushort> TV_UNICODE_CHAR;
	typedef std::vector<const IFont::CHAR_INFO*> TV_CHAR_INFO;

public:
	UIString(IFont* pFont);
	virtual ~UIString();

	virtual void Update(float dt);
	virtual void Render();

	bool SetText(const char* pszText);
	const char* GetText();

	void SetPosition(const Vector2& pos);
	const Vector2& GetPosition() const;

private:
	bool CreateCharVerts();
	void ClearCharVerts();

private:
	IFont* m_pFont;
	std::string m_strText;
	TV_UNICODE_CHAR m_UnicodeChars;
	int m_nCharCount;
	Vector2 m_vPosition;

	TV_CHAR_INFO m_vCharInfo;

};
#endif // __UISTRING_H__
