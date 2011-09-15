/*!
 * \file ClipTest.cpp
 * \date 2011/09/15 15:17
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "ClipTest.h"
#include <ui/IRendererUI.h>
#include <ui/IUIResMgr.h>
#include <util/IDebugUtil.h>
ClipTest::ClipTest( UIWindow* pParent )
:UIWindow(pParent)
{
	IUIResMgr::GetInstance().SetupDefaultButtonTextures(m_pStyle);
	m_fx = 0.0f;
	m_fy = 0.0f;
	m_fwidth = 0.0f;
	m_fheight = 0.0f;
}

ClipTest::~ClipTest()
{
	//TODO:
}

void ClipTest::Update( float dt )
{
	//TODO:
}

void ClipTest::Render( const RenderParam& param )
{
	Vector2 posAbs = param.m_vBasePos + GetPosition();
	QUAD_VERT_POS_UV quad;
	IRendererUI::GetInstance().SetupQuad(quad, m_pStyle[DUS_BUTTON_DEFAULT], posAbs);
	IRendererUI::GetInstance().SetTexture(m_pStyle[DUS_BUTTON_DEFAULT]->pTexture);

	if (IRendererUI::GetInstance().ClipRect(quad, m_fx, m_fy, m_fwidth, m_fheight))
	{	
		IRendererUI::GetInstance().DrawRect(quad);
	}
}

Vector2 ClipTest::GetBestSize()
{
	return IMath::VEC2_ZERO;
}

bool ClipTest::OnClicked( const Vector2& pos )
{
	LOGE("Clip Test Click");
	return true;
}

void ClipTest::SetClip( float x, float y, float width, float height )
{
	m_fx = x;
	m_fy = y;
	m_fwidth = width;
	m_fheight = height;
}
