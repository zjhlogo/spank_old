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

UISliderBar::UISliderBar(UIWindow* pParent)
:UIWindow(pParent)
{
	m_nMinRange = SLIDERBAR_MIN_RANGE;
	m_nMaxRange = SLIDERBAR_MAX_RANGE;
	m_nCurrentPos = SLIDERBAR_DEFAULT_POS;

// 	// TODO: setup the default textures
// 	IUIResMgr::GetInstance().SetupDefaultSliderBarTextures(m_pStyle, DUS_SLIDERBAR_NUM);
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
//	// TODO: draw under states, ex: (normal, pressed, disabled ...)
//	Vector2 posAbs = param.m_vBasePos + GetPosition();
// 	DrawNormalBar(posAbs);
// 	DrawMaskBar(posAbs);
// 	DrawArrow(posAbs);
}

Vector2 UISliderBar::GetBestSize()
{
	// TODO: calculate the boundary of the sliderbar
	return IMath::VEC2_ZERO;
}

void UISliderBar::SetSliderRange(int nMinRange, int nMaxRange)
{
	m_nMinRange = nMinRange;
	m_nMaxRange = nMaxRange;
	// TODO: update 
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
// 	m_fPercent = pos.x / GetSize().x;
// 	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_fPercent);
// 	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchBegin(const Vector2& pos)
{
// 	m_fPercent = pos.x / GetSize().x;
// 	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_fPercent);
// 	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchMove(const Vector2& pos)
{
// 	m_fPercent = pos.x / GetSize().x;
// 	MsgSilder msgSlider(MsgSilder::ST_MOVE, m_fPercent);
// 	CallEvent(msgSlider);
	return true;
}

bool UISliderBar::OnTouchEnd(const Vector2& pos)
{
// 	m_fPercent = pos.x  / GetSize().x;
// 	MsgSilder msgSlider(MsgSilder::ST_END, m_fPercent);
// 	CallEvent(msgSlider);
	return true;
}

void UISliderBar::DrawMaskBar(Vector2& pos)
{
// 	// TODO: use following function to draw the piectures
// 	// 
// 	//           IRendererUI::DrawRect(const Vector2& pos, const IMAGE_PIECE* pImagePiece);
// 	//           IRendererUI::DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece);
// 	//           IRendererUI::ClipRect(QUAD_VERT_POS_UV& quadInOut, float x, float y, float width, float height);
// 	//
//
// 	if(!m_pMaskBar) return;
// 	float fMaskTextureX = (float)m_pMaskBar->GetWidth();
// 	float fMaskTextureY = (float)m_pMaskBar->GetHeight();
// 	QUAD_VERT_POS_UV quad;
//
// 	quad.verts[0].x = pos.x;
// 	quad.verts[0].y = pos.y + fMaskTextureY;
// 	quad.verts[0].z = 0.0f;
// 	quad.verts[0].u = 0.0f;
// 	quad.verts[0].v = 0.0f;
//
// 	quad.verts[1].x = pos.x;
// 	quad.verts[1].y = pos.y;
// 	quad.verts[1].z = 0.0f;
// 	quad.verts[1].u = 0.0f;
// 	quad.verts[1].v = 1.0f;
// 
// 	quad.verts[2].x = pos.x + fMaskTextureX * m_fPercent;
// 	quad.verts[2].y = pos.y + fMaskTextureY;
// 	quad.verts[2].z = 0.0f;
// 	quad.verts[2].u = m_fPercent;
// 	quad.verts[2].v = 0.0f;
// 
// 	quad.verts[3].x = pos.x + fMaskTextureX * m_fPercent;
// 	quad.verts[3].y = pos.y;
// 	quad.verts[3].z = 0.0f;
// 	quad.verts[3].u = m_fPercent;
// 	quad.verts[3].v = 1.0f;
// 
// 	IRendererUI::GetInstance().SetTexture(m_pMaskBar);
// 	IRendererUI::GetInstance().DrawRect(quad);
}

void UISliderBar::DrawNormalBar(Vector2& pos)
{
// 	// TODO: use following function to draw the piectures
// 	// 
// 	//           IRendererUI::DrawRect(const Vector2& pos, const IMAGE_PIECE* pImagePiece);
// 	//           IRendererUI::DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece);
// 	//           IRendererUI::ClipRect(QUAD_VERT_POS_UV& quadInOut, float x, float y, float width, float height);
// 	//
//
// 	if(!m_pNormalbar) return;
// 
// 	float fNormalTextureY = (float)m_pNormalbar->GetHeight();
// 	float fNormalTextureX = (float)m_pNormalbar->GetWidth();
// 	QUAD_VERT_POS_UV quad;
// 
// 	quad.verts[0].x = pos.x;
// 	quad.verts[0].y = pos.y + fNormalTextureY;
// 	quad.verts[0].z = 0.0f;
// 	quad.verts[0].u = 0.0f;
// 	quad.verts[0].v = 0.0;
// 
// 	quad.verts[1].x = pos.x;
// 	quad.verts[1].y = pos.y;
// 	quad.verts[1].z = 0.0f;
// 	quad.verts[1].u = 0.0f;
// 	quad.verts[1].v = 1.0f;
// 
// 	quad.verts[2].x = pos.x + fNormalTextureX;
// 	quad.verts[2].y = pos.y + fNormalTextureY;
// 	quad.verts[2].z = 0.0f;
// 	quad.verts[2].u = 1.0f;
// 	quad.verts[2].v = 0.0f;
// 
// 	quad.verts[3].x = pos.x + fNormalTextureX;
// 	quad.verts[3].y = pos.y;
// 	quad.verts[3].z = 0.0f;
// 	quad.verts[3].u = 1.0f;
// 	quad.verts[3].v = 1.0f;
// 
// 	IRendererUI::GetInstance().SetTexture(m_pNormalbar);
// 	IRendererUI::GetInstance().DrawRect(quad);
}

void UISliderBar::DrawArrow(Vector2& pos)
{
// 	// TODO: use following function to draw the piectures
// 	// 
// 	//           IRendererUI::DrawRect(const Vector2& pos, const IMAGE_PIECE* pImagePiece);
// 	//           IRendererUI::DrawRect(float x, float y, const IMAGE_PIECE* pImagePiece);
// 	//           IRendererUI::ClipRect(QUAD_VERT_POS_UV& quadInOut, float x, float y, float width, float height);
// 	//
//
// 	if(!m_pArrow) return;
// 
// 	float fNormalTextureY = (float)m_pArrow->GetHeight();
// 	float fNormalTextureX = (float)m_pArrow->GetWidth();
// 	
// 	if(m_pMaskBar == NULL) return;
// 	float fPosX = pos.x + m_fPercent * m_pMaskBar->GetWidth() - fNormalTextureX /2.0f ;
// 	float fPosY = pos.y - (fNormalTextureY - m_pMaskBar->GetHeight()) / 2.0f; 
// 
// 	QUAD_VERT_POS_UV quad;
// 
// 	quad.verts[0].x = fPosX;
// 	quad.verts[0].y = fPosY + fNormalTextureY;
// 	quad.verts[0].z = 0.0f;
// 	quad.verts[0].u = 0.0f;
// 	quad.verts[0].v = 0.0;
// 
// 	quad.verts[1].x = fPosX;
// 	quad.verts[1].y = fPosY;
// 	quad.verts[1].z = 0.0f;
// 	quad.verts[1].u = 0.0f;
// 	quad.verts[1].v = 1.0f;
// 
// 	quad.verts[2].x = fPosX + fNormalTextureX;
// 	quad.verts[2].y = fPosY + fNormalTextureY;
// 	quad.verts[2].z = 0.0f;
// 	quad.verts[2].u = 1.0f;
// 	quad.verts[2].v = 0.0f;
// 
// 	quad.verts[3].x = fPosX + fNormalTextureX;
// 	quad.verts[3].y = fPosY;
// 	quad.verts[3].z = 0.0f;
// 	quad.verts[3].u = 1.0f;
// 	quad.verts[3].v = 1.0f;
// 
// 	IRendererUI::GetInstance().SetTexture(m_pArrow);
// 	IRendererUI::GetInstance().DrawRect(quad);
}
