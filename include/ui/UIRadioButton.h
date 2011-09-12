/*!
 * \file UIRadioButton.h
 * \date 2011/09/08 10:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __UIRADIO_H__
#define __UIRADIO_H__

#include "UIWindow.h"
#include "UIString.h"

class UIRadioButton : public UIWindow
{
public:
	UIRadioButton(UIWindow* pParent);
	virtual ~UIRadioButton();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);

	void SetGroupID(int nGroup);
	int GetGroupID() const;

	void SetText(const char* pszText);
	void SetStyle(const char* pszStyle);

	virtual bool OnClicked(const Vector2& pos);

private:
	int m_nGroupID;
	UIString* m_pString;

};

#endif // __UIRADIO_H__
