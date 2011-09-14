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

class UISliderBar : public UIWindow
{
public:
	enum CONST_DEFINE
	{
		SLIDERBAR_MIN_RANGE = 0,
		SLIDERBAR_MAX_RANGE = 100,
		SLIDERBAR_DEFAULT_POS = 50,
	};

public:
	DECLARE_RTTI(UISliderBar, UIWindow);

	UISliderBar(UIWindow* pParent);
	virtual ~UISliderBar();

	virtual void Update(float dt);
	virtual void Render(const RenderParam& param);
	virtual Vector2 GetBestSize();

	void SetSliderRange(int nMinRange, int nMaxRange);
	void SetCurrentPos(int nPos);

	bool SetSliderBarTexture(const IMAGE_PIECE* pImagePiece, int nIndex);

	virtual bool OnClicked(const Vector2& pos);
	virtual bool OnTouchBegin(const Vector2& pos);
	virtual bool OnTouchMove(const Vector2& pos);
	virtual bool OnTouchEnd(const Vector2& pos);

private:
	void DrawMaskBar(Vector2& pos);
	void DrawNormalBar(Vector2& pos);
	void DrawArrow(Vector2& pos);

private:
	int m_nMinRange;
	int m_nMaxRange;
	int m_nCurrentPos;
	const IMAGE_PIECE* m_pStyle[DUS_SLIDERBAR_NUM];

};
#endif // __UISILDERBAR_H__