/*!
 * \file UITextView.h
 * \date 8-24-2011 15:23:01
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UITEXTVIEW_H__
#define __UITEXTVIEW_H__

#include "UIWindow.h"
#include "UIString.h"

class UITextView : public UIWindow
{
public:
	UITextView(UIWindow* pParent, const char* pszText);
	virtual ~UITextView();

	void SetText(const char* pszText);

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	virtual Vector2 GetBestSize();

	virtual bool OnClicked(const Vector2& pos);

private:
	UIString* m_pString;

};
#endif // __UITEXTVIEW_H__
