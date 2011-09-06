/*!
 * \file UISilder.cpp
 * \date 2011/09/05 16:15
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UISilder.h>
#include <msg/MsgSlider.h>
#include <util/IDebugUtil.h>
#include <ui/IRendererUI.h>
UISilder::UISilder( UIWindow* pParent )
: UIWindow(pParent)
{
	
	m_pMaskBar = NULL;
	m_pNormalbar = NULL;
	m_pArrow = NULL;
	m_fPercent = 0.5f;
}
UISilder::~UISilder()
{
	//TODO:
}

void UISilder::Update( float dt )
{
	//TODO:
}

void UISilder::Render( const RenderParam& param )
{
	//TODO:
	Vector2 pos = param.m_vBasePos + GetPosition();
	DrawNormalBar(pos);
	DrawMaskBar(pos);
	DrawArrow(pos);
}

void UISilder::SetArrowTexture( ITexture* pTexture )
{
	if(!pTexture) return;
	m_pArrow = pTexture;
	float fwidth = (float)pTexture->GetWidth();
	float fHeight = (float)pTexture->GetHeight();
	if(fHeight > GetSize().y)
		SetSize(Vector2(GetSize().x, fHeight));

}

void UISilder::SetMaskBarTexture( ITexture* pTexture )
{
	//TODO:
	if(!pTexture) return;
	m_pMaskBar = pTexture;
	float fwidth = (float)pTexture->GetWidth();
	float fHeight = (float)pTexture->GetHeight();
	SetSize(Vector2(fwidth, fHeight));
}

void UISilder::SetNormalBarTexture( ITexture* pTexture )
{
	//TODO:
	if(!pTexture) return;
	m_pNormalbar = pTexture;
	float fwidth = (float)pTexture->GetWidth();
	float fHeight = (float)pTexture->GetHeight();
	SetSize(Vector2(fwidth, fHeight));
}

bool UISilder::OnClicked( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

bool UISilder::OnTouchBegin( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_BEGIN, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

bool UISilder::OnTouchMove( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_MOVE, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

bool UISilder::OnTouchEnd( const Vector2& pos )
{
	//TODO:
	m_fPercent = pos.x  / GetSize().x;
	MsgSilder msgSlider(MsgSilder::ST_END, m_fPercent);
	CallEvent(msgSlider);
	return true;
}

void UISilder::DrawMaskBar(  Vector2& pos )
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

void UISilder::DrawNormalBar( Vector2& pos )
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

void UISilder::DrawArrow( Vector2& pos )
{
	if(!m_pArrow) return;

	float fNormalTextureY = (float)m_pArrow->GetHeight();
	float fNormalTextureX = (float)m_pArrow->GetWidth();

	float fPosX = pos.x + m_fPercent * m_pNormalbar->GetWidth() - fNormalTextureX /2.0f ;
	float fPosY = pos.y  - (fNormalTextureY - m_pNormalbar->GetHeight()) / 2.0f; 

	
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








