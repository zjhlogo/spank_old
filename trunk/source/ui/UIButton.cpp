/*!
 * \file UIButton.cpp
 * \date 2011/09/05 9:32
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <ui/UIButton.h>
#include <util/IDebugUtil.h>
#include <ITextureMgr.h>
#include <ui/IRendererUI.h>
#include <msg/MsgID.h>
UIButton::UIButton(UIWindow *pParent)
:UIWindow(pParent)
{
	//TODO
	m_pString = NULL;
	m_pNormalTexture = NULL;
	m_pCheckedTexture = NULL;
	m_bCheckState = false;
}
UIButton::~UIButton(void)
{
	//TODO:
	SAFE_RELEASE(m_pCheckedTexture);
	SAFE_RELEASE(m_pNormalTexture);
	SAFE_DELETE(m_pString);
}


void UIButton::SetText( char* pszText )
{
	if(pszText == NULL) return;
	m_pString = new UIString(pszText);
	m_pString->SetText(pszText);
}

void UIButton::SetNormalTexture( ITexture* pTexture )
{
	if(pTexture == NULL) return;

	m_pNormalTexture = pTexture;
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

void UIButton::SetCheckedTexture( ITexture* pTexture )
{
	if(pTexture== NULL)return;

	m_pCheckedTexture = pTexture;
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

void UIButton::Render( const RenderParam& param )
{
	//TODO:

	if( m_pCheckedTexture== NULL && m_pNormalTexture == NULL)
		return;
	Vector2 vrefPos = param.m_vBasePos + GetPosition();

	QUAD_VERT_POS_UV quad;
	quad.verts[0].x = vrefPos.x;
	quad.verts[0].y = vrefPos.y + GetSize().y;
	quad.verts[0].z = 0.0f;
	quad.verts[0].u = 0.0f;
	quad.verts[0].v = 0.0;

	quad.verts[1].x = vrefPos.x;
	quad.verts[1].y = vrefPos.y;
	quad.verts[1].z = 0.0f;
	quad.verts[1].u = 0.0f;
	quad.verts[1].v = 1.0f;

	quad.verts[2].x = vrefPos.x + GetSize().x;
	quad.verts[2].y = vrefPos.y + GetSize().y;
	quad.verts[2].z = 0.0f;
	quad.verts[2].u = 1.0f;
	quad.verts[2].v = 0.0f;

	quad.verts[3].x = vrefPos.x + GetSize().x;
	quad.verts[3].y = vrefPos.y;
	quad.verts[3].z = 0.0f;
	quad.verts[3].u = 1.0f;
	quad.verts[3].v = 1.0f;

	if(m_bCheckState)
		IRendererUI::GetInstance().SetTexture(m_pCheckedTexture);
	else
		IRendererUI::GetInstance().SetTexture(m_pNormalTexture);
	IRendererUI::GetInstance().DrawTriangleRect(quad);

	if(m_pString != NULL)
	{
		IRendererUI::GetInstance().Flush();

		vrefPos += GetPaddingLeftTop();
		if(m_pString!=NULL)
			m_pString->Render(vrefPos);
	}
}

void UIButton::Update( float dt )
{
	//TODO:
}

bool UIButton::GetCheckState() const
{
	return m_bCheckState;
}

void UIButton::SetCheckedState( bool bflag )
{
	m_bCheckState = bflag;
}

bool UIButton::OnClicked(const Vector2& pos)
{  
	MsgClick msgclick(MsgClick::CT_CHECK, GetID());
	CallEvent(msgclick);
	return true;
}

bool UIButton::OnTouchBegin( const Vector2& pos )
{
	SetCheckedState(true);
	return true;
}

bool UIButton::OnTouchMove( const Vector2& pos )
{
	SetCheckedState(false);
	return true;
}

bool UIButton::OnTouchEnd( const Vector2& pos )
{
	SetCheckedState(false);
	return true;
}

