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
	virtual Vector2 GetBestSize();

	void SetGroupID(int nGroup);
	int GetGroupID() const;

	void SetText(const char* pszText);

	void SetCheck(bool bCheck);
	bool IsChecked() const;

	bool SetRadioButtonTexture(const IMAGE_PIECE* pImagePiece, int nIndex);

	virtual bool OnClicked(const Vector2& pos);

private:
	int m_nGroupID;
	UIString* m_pString;
	bool m_bCheck;
	const IMAGE_PIECE* m_pStyle[DUS_RADIOBUTTON_NUM];

};

#endif // __UIRADIO_H__
