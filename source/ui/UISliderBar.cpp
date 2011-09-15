/*!
 * \file UISliderBar.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UISliderBar.h>
#include <ui/IRendererUI.h>
#include <msg/MsgSlider.h>
#include <util/IDebugUtil.h>
#include <ui/IUIResMgr.h>
UISliderBar::UISliderBar(UIWindow* pParent)
:UIWindow(pParent)
{
	m_nMinRange = SLIDERBAR_MIN_RANGE;
	m_nMaxRange = SLIDERBAR_MAX_RANGE;
	m_nCurrentPos = SLIDERBAR_DEFAULT_POS;

	IUIResMgr::GetInstance().SetupDefaultSliderBarTextures(m_pStyle, DUS_SLIDERBAR_NUM);
	AdjustSize();
}

UISliderBar::~UISliderBar()
{
	// TODO: 
}

void UISliderBar::Update(float dt)
{
	// TODO: 
}

void UISliderBar::Render(const RenderParam& param)
{
	RenderBorder(param);
	Vector2 posAbs = param.m_vBasePos + GetPosition();
	//AdjustPosition
	if( m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height > m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height)
	{
		posAbs.y = posAbs.y + (m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height - m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) /2.0f;
	}

	if(! IsEnable() || !param.IsEnable())
	{
		//render disabled state;
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_SLIDERBAR_THUMB_DISABLED]);
	}
	else
	{
		//render the background
		IRendererUI::GetInstance().DrawRect(posAbs, m_pStyle[DUS_SLIDERBAR_BACKGROUND]);
		//render the foreground
		//calculate the size of the new foreground to render
		float Aplaha = (float)m_nCurrentPos / (m_nMaxRange - m_nMinRange);
		IMAGE_PIECE ImagePiece;
		IRendererUI::GetInstance().ClipRect(m_pStyle[DUS_SLIDERBAR_FOREGROUND], ImagePiece, 0.0f, 0.0f, Aplaha, 1.0f);
		IRendererUI::GetInstance().DrawRect(posAbs, &ImagePiece);
		 if( IsPressed())
		{
			// render pressed state
			//calculate the position of the Arrow to render
			float fposx = posAbs.x + m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width * Aplaha - m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED]->width / 2.0f;
			float fposy = posAbs.y - (m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED]->height - m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) / 2.0f;
			IRendererUI::GetInstance().DrawRect(fposx,fposy, m_pStyle[DUS_SLIDERBAR_THUMB_PRESSED]);
		}
		else
		{
			// render default state
			//calculate the position of the Arrow to render
			float fposx = posAbs.x + m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width * Aplaha - m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->width / 2.0f;
			float fposy = posAbs.y - (m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height - m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height) / 2.0f;
			IRendererUI::GetInstance().DrawRect(fposx,fposy, m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]);
		}
	}
}

Vector2 UISliderBar::GetBestSize()
{
	// TODO: calculate the boundary of the sliderbar
	Vector2 sizeMax = Vector2(m_pStyle[DUS_SLIDERBAR_BACKGROUND]->width, m_pStyle[DUS_SLIDERBAR_BACKGROUND]->height);
	if (sizeMax.x < m_pStyle[DUS_SLIDERBAR_FOREGROUND]->width) sizeMax.x = m_pStyle[DUS_SLIDERBAR_FOREGROUND]->width;
	if (sizeMax.y < m_pStyle[DUS_SLIDERBAR_FOREGROUND]->height) sizeMax.y = m_pStyle[DUS_SLIDERBAR_FOREGROUND]->height;
	if (sizeMax.y < m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height) sizeMax.y = m_pStyle[DUS_SLIDERBAR_THUMB_DEFAULT]->height;

	return sizeMax;
}

void UISliderBar::SetSliderRange(int nMinRange, int nMaxRange)
{
	m_nMinRange = nMinRange;
	m_nMaxRange = nMaxRange;
}

void UISliderBar::SetCurrentPos(int nPos)
{
	m_nCurrentPos = nPos;
}

bool UISliderBar::SetSliderBarTexture(const IMAGE_PIECE* pImagePiece, int nIndex)
{
	if (nIndex < 0 || nIndex >= DUS_SLIDERBAR_NUM) return false;

	m_pStyle[nIndex] = pImagePiece;
	AdjustSize();
	return true;
}

bool UISliderBar::OnClicked(const Vector2& pos)
{

	m_nCurrentPos = int(pos.x / GetBestSize().x * (m_nMaxRange - m_nMinRange));
	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_nCurrentPos);
	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchBegin(const Vector2& pos)
{
	m_nCurrentPos = int(pos.x / GetBestSize().x * (m_nMaxRange - m_nMinRange));
	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_nCurrentPos);
	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchMove(const Vector2& pos)
{
	m_nCurrentPos = int(pos.x / GetBestSize().x * (m_nMaxRange - m_nMinRange));
	MsgSilder msgSlider(MsgSilder::ST_MOVE, m_nCurrentPos);
	CallEvent(msgSlider);

	return true;
}

bool UISliderBar::OnTouchEnd(const Vector2& pos)
{
	m_nCurrentPos = int(pos.x / GetBestSize().x * (m_nMaxRange - m_nMinRange));
	MsgSilder msgSlider(MsgSilder::ST_END, m_nCurrentPos);
	CallEvent(msgSlider);
	return true;
}

