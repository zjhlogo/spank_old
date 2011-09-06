/*!
 * \file UIButton.cpp
 * \date 2011/09/05 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIButton.h>
#include <ui/IRendererUI.h>
#include <ITexture.h>
#include <util/IDebugUtil.h>
#include <msg/MsgID.h>
UIButton::UIButton(UIWindow *pParent)
:UIWindow(pParent)
{
	m_pString = NULL;
	m_pNormaldTexture = NULL;
	m_pPressedtexture = NULL;
	m_bIsVisual = true;
	m_State = MsgClick::CT_NORMAL;
}

UIButton::~UIButton(void)
{
	SAFE_DELETE(m_pString);
}

void UIButton::SetText(const char *pszText)
{
	m_pString = new UIString(pszText);
	m_pString->SetText(pszText);
	SetSize(m_pString->GetSize());
}

void UIButton::SetNormalTexture(ITexture *pTexture)
{
	m_pNormaldTexture = pTexture;
	float fWidth = (float)pTexture->GetWidth();
	float fheight = (float)pTexture->GetHeight();
	SetSize(Vector2(fWidth, fheight));
	
}

void UIButton::SetPressedTexture( ITexture* pTexture )
{
	m_pPressedtexture = pTexture;
	float fWidth = (float)pTexture->GetWidth();
	float fheight = (float)pTexture->GetHeight();
	SetSize(Vector2(fWidth, fheight));
}

void UIButton::Update(float dt)
{
	//TODO:
}

void UIButton::Render(const RenderParam &param)
{
	//TODO:
	if(!m_bIsVisual) return;

	Vector2 pos = param.m_vBasePos + GetPosition();
	if( m_pPressedtexture!= NULL || m_pNormaldTexture!= NULL)
	{
		QUAD_VERT_POS_UV quad;
		quad.verts[0].x = pos.x;
		quad.verts[0].y = pos.y + GetSize().y;
		quad.verts[0].z = 0.0f;
		quad.verts[0].u = 0.0f;
		quad.verts[0].v = 0.0;

		quad.verts[1].x = pos.x;
		quad.verts[1].y = pos.y;
		quad.verts[1].z = 0.0f;
		quad.verts[1].u = 0.0f;
		quad.verts[1].v = 1.0f;

		quad.verts[2].x = pos.x + GetSize().x;
		quad.verts[2].y = pos.y + GetSize().y;
		quad.verts[2].z = 0.0f;
		quad.verts[2].u = 1.0f;
		quad.verts[2].v = 0.0f;

		quad.verts[3].x = pos.x + GetSize().x;
		quad.verts[3].y = pos.y;
		quad.verts[3].z = 0.0f;
		quad.verts[3].u = 1.0f;
		quad.verts[3].v = 1.0f;
		
		if( m_State == MsgClick::CT_NORMAL)
			IRendererUI::GetInstance().SetTexture(m_pNormaldTexture);
		else
			IRendererUI::GetInstance().SetTexture(m_pPressedtexture);
		
		IRendererUI::GetInstance().DrawTriangleRect(quad);
	}
	else
		IRendererUI::GetInstance().DrawLineRect(pos, GetSize());

	IRendererUI::GetInstance().Flush();

	pos += GetPaddingLeftTop();
	if(m_pString!=NULL)
		m_pString->Render(pos);
	
}

bool UIButton::OnClicked(const Vector2& pos)
{  
	if(!m_bIsVisual) return true;
	MsgClick msgclick(m_State, pos);
	CallEvent(msgclick);
	return true;
}

void UIButton::SetVisual(bool IsVisual)
{
	m_bIsVisual = IsVisual;
}

bool UIButton::OnTouchBegin( const Vector2& pos )
{
	m_State = MsgClick::CT_PRESSED;
	return true;
	//TODO:
}

bool UIButton::OnTouchMove( const Vector2& pos )
{
	if( !PointInRect(pos, GetPosition(),GetSize()))
		m_State = MsgClick::CT_NORMAL;
	return true;
	//TODO:
}

bool UIButton::OnTouchEnd( const Vector2& pos )
{
	m_State = MsgClick::CT_NORMAL;
	return true;
	//TODO:
}
