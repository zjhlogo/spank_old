/*!
 * \file UISilder.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UISlider.h>
#include <msg/MsgSlider.h>
#include <util/IDebugUtil.h>
#include <ui/IRendererUI.h>
UISlider::UISlider( UIWindow* pParent )
: UIWindow(pParent)
{
	
	m_pMaskBar = NULL;
	m_pNormalbar = NULL;
	m_pArrow = NULL;
	m_fPercent = 0.5f;
}
UISlider::~UISlider()
{
	//TODO:
	SAFE_RELEASE(m_pNormalbar);
	SAFE_RELEASE(m_pMaskBar);
	SAFE_RELEASE(m_pArrow);
}

void UISlider::Update( float dt )
{
	//TODO:
}

void UISlider::Render( const RenderParam& param )
{
	//TODO:
	Vector2 pos = param.m_vBasePos + GetPosition();
	DrawNormalBar(pos);
	DrawMaskBar(pos);
	DrawArrow(pos);
}

void UISlider::SetArrowTexture( ITexture* pTexture )
{
	if(!pTexture) return;
	
	m_pArrow = pTexture;
	float fWidth = 0.0f;
	float fHeight = 0.0f;
	fWidth = (float)pTexture->GetWidth();
	fHeight = (float)pTexture->GetHeight();
	if( fWidth < GetSize().x)
		fWidth = GetSize().x;
	if (fHeight < GetSize().y)
		fHeight = GetSize().y;

	SetSize(Vector2(fWidth, fHeight));

}

void UISlider::SetMaskBarTexture( ITexture* pTexture )
{
	//TODO:
	if(!pTexture) return;
	m_pMaskBar = pTexture;
	float fWidth = 0.0f;
	float fHeight = 0.0f;
	fWidth = (float)pTexture->GetWidth();
	fHeight = (float)pTexture->GetHeight();
	if( fWidth < GetSize().x)
		fWidth = GetSize().x;
	if (fHeight < GetSize().y)
		fHeight = GetSize().y;

	SetSize(Vector2(fWidth, fHeight));
}

void UISlider::SetNormalBarTexture( ITexture* pTexture )
{
	//TODO:
	if(!pTexture) return;
	m_pNormalbar = pTexture;
	float fWidth = 0.0f;
	float fHeight = 0.0f;
	fWidth = (float)pTexture->GetWidth();
	fHeight = (float)pTexture->GetHeight();
	if( fWidth < GetSize().x)
		fWidth = GetSize().x;
	if (fHeight < GetSize().y)
		fHeight = GetSize().y;

	SetSize(Vector2(fWidth, fHeight));
}

bool UISlider::OnClicked( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

bool UISlider::OnTouchBegin( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

bool UISlider::OnTouchMove( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_MOVE, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

bool UISlider::OnTouchEnd( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x  / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_END, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

void UISlider::DrawMaskBar(  Vector2& pos )
{
	if(!m_pMaskBar) return;
	float fMaskTextureX = (float)m_pMaskBar->GetWidth();
	float fMaskTextureY = (float)m_pMaskBar->GetHeight();
	QUAD_VERT_POS_UV quad;

	quad.verts[0].x = pos.x;
	quad.verts[0].y = pos.y + fMaskTextureY;
	quad.verts[0].z = 0.0f;
	quad.verts[0].u = 0.0f;
	quad.verts[0].v = 0.0;

	quad.verts[1].x = pos.x;
	quad.verts[1].y = pos.y;
	quad.verts[1].z = 0.0f;
	quad.verts[1].u = 0.0f;
	quad.verts[1].v = 1.0f;

	quad.verts[2].x = pos.x + fMaskTextureX * m_fPercent;
	quad.verts[2].y = pos.y + fMaskTextureY;
	quad.verts[2].z = 0.0f;
	quad.verts[2].u = m_fPercent;
	quad.verts[2].v = 0.0f;

	quad.verts[3].x = pos.x + fMaskTextureX * m_fPercent;
	quad.verts[3].y = pos.y;
	quad.verts[3].z = 0.0f;
	quad.verts[3].u = m_fPercent;
	quad.verts[3].v = 1.0f;
	
	IRendererUI::GetInstance().SetTexture(m_pMaskBar);
	IRendererUI::GetInstance().DrawTriangleRect(quad);
}

void UISlider::DrawNormalBar( Vector2& pos )
{
	if(!m_pNormalbar) return;

	float fNormalTextureY = (float)m_pNormalbar->GetHeight();
	float fNormalTextureX = (float)m_pNormalbar->GetWidth();
	QUAD_VERT_POS_UV quad;

	quad.verts[0].x = pos.x;
	quad.verts[0].y = pos.y + fNormalTextureY;
	quad.verts[0].z = 0.0f;
	quad.verts[0].u = 0.0f;
	quad.verts[0].v = 0.0;

	quad.verts[1].x = pos.x;
	quad.verts[1].y = pos.y;
	quad.verts[1].z = 0.0f;
	quad.verts[1].u = 0.0f;
	quad.verts[1].v = 1.0f;

	quad.verts[2].x = pos.x + fNormalTextureX;
	quad.verts[2].y = pos.y + fNormalTextureY;
	quad.verts[2].z = 0.0f;
	quad.verts[2].u = 1.0f;
	quad.verts[2].v = 0.0f;

	quad.verts[3].x = pos.x + fNormalTextureX;
	quad.verts[3].y = pos.y;
	quad.verts[3].z = 0.0f;
	quad.verts[3].u = 1.0f;
	quad.verts[3].v = 1.0f;

	IRendererUI::GetInstance().SetTexture(m_pNormalbar);
	IRendererUI::GetInstance().DrawTriangleRect(quad);
}

void UISlider::DrawArrow( Vector2& pos )
{
	if(!m_pArrow) return;

	float fNormalTextureY = (float)m_pArrow->GetHeight();
	float fNormalTextureX = (float)m_pArrow->GetWidth();
	
	if(m_pMaskBar == NULL) return;
	float fPosX = pos.x + m_fPercent * m_pMaskBar->GetWidth() - fNormalTextureX /2.0f ;
	float fPosY = pos.y - (fNormalTextureY - m_pMaskBar->GetHeight()) / 2.0f; 

	
	QUAD_VERT_POS_UV quad;

	quad.verts[0].x = fPosX;
	quad.verts[0].y = fPosY + fNormalTextureY;
	quad.verts[0].z = 0.0f;
	quad.verts[0].u = 0.0f;
	quad.verts[0].v = 0.0;

	quad.verts[1].x = fPosX;
	quad.verts[1].y = fPosY;
	quad.verts[1].z = 0.0f;
	quad.verts[1].u = 0.0f;
	quad.verts[1].v = 1.0f;

	quad.verts[2].x = fPosX + fNormalTextureX;
	quad.verts[2].y = fPosY + fNormalTextureY;
	quad.verts[2].z = 0.0f;
	quad.verts[2].u = 1.0f;
	quad.verts[2].v = 0.0f;

	quad.verts[3].x = fPosX + fNormalTextureX;
	quad.verts[3].y = fPosY;
	quad.verts[3].z = 0.0f;
	quad.verts[3].u = 1.0f;
	quad.verts[3].v = 1.0f;

	IRendererUI::GetInstance().SetTexture(m_pArrow);
	IRendererUI::GetInstance().DrawTriangleRect(quad);

}








