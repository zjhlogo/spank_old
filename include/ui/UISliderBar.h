/*!
 * \file UISliderBar.h
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqng(wbaoqing@gmail.com)
 */
#ifndef __UISILDERBAR_H__
#define __UISILDERBAR_H__

#include "UIWindow.h"
#include "../ITexture.h"

class UISliderBar : public UIWindow
{
public:
	UISliderBar(UIWindow* pParent);
	virtual ~UISliderBar();

	void Update(float dt);
	void Render(const RenderParam& param);

	void SetArrowTexture(ITexture* pTexture);
	void SetMaskBarTexture(ITexture* pTexture);
	void SetNormalBarTexture(ITexture* pTexture);

	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);

private:
	void DrawMaskBar(Vector2& pos);
	void DrawNormalBar(Vector2& pos);
	void DrawArrow(Vector2& pos);

private:
	ITexture* m_pMaskBar;
	ITexture* m_pNormalbar;
	ITexture* m_pArrow;
	float m_fPercent;

};
#endif // __UISILDERBAR_H__
