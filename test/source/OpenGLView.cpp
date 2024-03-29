/*!
 * \file OpenGLView.cpp
 * \date 11-08-2011 11:22:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "OpenGLView.h"
#include <util/ScreenUtil.h>
#include <util/IDebugUtil.h>
#include <util/StringUtil.h>
#include <msg/MsgMgr.h>
#include <msg/MsgTouch.h>
#include <msg/MsgKey.h>

#include <ui/uimsg/MsgClick.h>
#include <ui/uimsg/UIMsgID.h>
#include <ui/IUISystem.h>
#include <ui/UITextView.h>
#include <ui/IRendererUI.h>
#include <osui/IOSUISystem.h>

#include <IResourceMgr.h>
#include <IRenderer2D.h>

#include "UserMsgID.h"
#include "UITestCase.h"
#include "SpriteTestCase.h"
#include "ActionTestCase.h"
#include "ParticleTestCase.h"
#include "MapTestCase.h"
#include "Box2DTestCase.h"
#include "ClipRectTestCase.h"
#include "TweenTestCase.h"
#include "PorkerTestCase.h"
#include "NetworkTestCase.h"
#include "ExitTestCase.h"

OpenGLView::OpenGLView()
{
	m_pCurrTestCase = NULL;
	m_pMainScreen = NULL;
	m_pListView = NULL;
	m_pFPS = NULL;
	m_nFPS = 0;
	m_fFPSTime = 0.0f;
	m_nIndex = 0;
}

OpenGLView::~OpenGLView()
{
	// TODO: 
}

bool OpenGLView::Initialize()
{
	MsgMgr::GetInstance().SubscribeMessage(MI_TOUCH, this, (MSG_CALLBACK)&OpenGLView::OnMsgTouch);

	m_pCurrTestCase = NULL;

	IResourceMgr::GetInstance().AddImagePieceList("test_case.xml");
	IResourceMgr::GetInstance().AddImagePieceList("Porker.xml");
	m_pMainScreen = IUISystem::GetInstance().GetCurrentScreen();
	m_pListView = new UIListView(m_pMainScreen);
	m_pListView->SetSize(m_pMainScreen->GetSize());

	m_pFPS = new UIString("FPS: %d");
	m_nFPS = 0;
	m_fFPSTime = 0.0f;

	// add test case
	AddTestCase(new UITestCase(), m_pMainScreen);
	AddTestCase(new SpriteTestCase(), m_pMainScreen);
	AddTestCase(new ActionTestCase(), m_pMainScreen);
	AddTestCase(new ParticleTestCase(), m_pMainScreen);
	AddTestCase(new MapTestCase(), m_pMainScreen);
	AddTestCase(new Box2DTestCase(), m_pMainScreen);
	AddTestCase(new ClipRectTestCase(), m_pMainScreen);
	AddTestCase(new TweenTestCase(), m_pMainScreen);
	AddTestCase(new PorkerTestCase(), m_pMainScreen);
	AddTestCase(new NetworkTestCase(), m_pMainScreen);
	AddTestCase(new ExitTestCase(), m_pMainScreen);
	m_pListView->ArrangeItems();
	return true;
}

void OpenGLView::Terminate()
{
	RemoveCurrTestCase();

	SAFE_DELETE(m_pFPS);
	m_nFPS = 0;
	m_fFPSTime = 0.0f;

	// free test case
	for (TV_TEST_CASE::iterator it = m_vTestCase.begin(); it != m_vTestCase.end(); ++it)
	{
		TestCase* pTestCase = (*it);
		SAFE_DELETE(pTestCase);
	}
	m_vTestCase.clear();

	m_pListView = NULL;
	MsgMgr::GetInstance().UnsubscribeMessage(MI_TOUCH, this);
}

void OpenGLView::Update(float dt)
{
	m_fFPSTime += dt;
	m_nFPS++;
	if (m_fFPSTime > 1.0f)
	{
		m_fFPSTime -= 1.0f;
		char szBuffer[128];
		StringUtil::Format(szBuffer, 128, "FPS: %d", m_nFPS);
		m_pFPS->SetText(szBuffer);
		m_nFPS = 0;
	}

	if (m_pCurrTestCase) m_pCurrTestCase->Update(dt);
	IUISystem::GetInstance().Update(dt);
}

void OpenGLView::Render()
{
	// render test case
	IRenderer2D::GetInstance().BeginRender();
	if (m_pCurrTestCase) m_pCurrTestCase->Render();
	IRenderer2D::GetInstance().EndRender();

	// render ui
	IRendererUI::GetInstance().BeginRender();
	IUISystem::GetInstance().Render();
	if (m_pFPS) m_pFPS->Render(Vector2(0.0f, 0.0f), Vector2(0.0f, 0.0f), m_pFPS->GetSize());
	IRendererUI::GetInstance().EndRender();
}

bool OpenGLView::OnMsgTouch(IMsgBase* pMsg)
{
	MsgTouch* pMsgTouch = (MsgTouch*)pMsg;

	if (pMsgTouch->IsTouchBegin())
	{
// 		LOGD("touch begin: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_BEGIN);
	}
	else if (pMsgTouch->IsTouchMove())
	{
// 		LOGD("touch move: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_MOVE);
	}
	else if (pMsgTouch->IsTouchEnd())
	{
// 		LOGD("touch end: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
		IUISystem::GetInstance().ProcessTouchEvent(pMsgTouch->GetPosition(), UTET_END);
	}

	return true;
}

bool OpenGLView::OnBtnTestCaseClicked(IMsgBase* pMsg)
{
	MsgClick* pMsgClick = (MsgClick*)pMsg;

	// switch to the new test case
	SwitchTestCase(pMsgClick->GetSenderID());

	return true;
}

bool OpenGLView::OnBtnReturnClicked(IMsgBase* pMsg)
{
	// free current test case
	RemoveCurrTestCase();
	return true;
}

bool OpenGLView::AddTestCase(TestCase* pTestCase, UIScreen* pScreen)
{
	if (!pTestCase) return false;

	int nIndex = (int)m_vTestCase.size();

	UITextView* pTextView = new UITextView(m_pListView, IMath::VEC2_ZERO, pTestCase->GetName());
	pTextView->SetID(nIndex);
	pTextView->ConnectEvent(UMI_CLICKED, this, (MSG_CALLBACK)&OpenGLView::OnBtnTestCaseClicked);

	m_vTestCase.push_back(pTestCase);
	pTestCase->ConnectEvent(MI_USER_RETURN, this, (MSG_CALLBACK)&OpenGLView::OnBtnReturnClicked);

	return true;
}

void OpenGLView::RemoveCurrTestCase()
{
	if (m_pCurrTestCase)
	{
		m_pCurrTestCase->InternalTerminate();
		IUISystem::GetInstance().SetCurrentScreen(m_pMainScreen);
		m_pCurrTestCase = NULL;
	}
}

bool OpenGLView::SwitchTestCase(int nIndex)
{
	if (nIndex < 0 && nIndex >= (int)m_vTestCase.size()) return false;

	TestCase* pTestCase = m_vTestCase[nIndex];
	if (pTestCase != m_pCurrTestCase) RemoveCurrTestCase();

	if (!pTestCase->InternalInitialize())
	{
		pTestCase->InternalTerminate();
		LOGE("initialize test case failed %s", pTestCase->GetName());
		return false;
	}

	m_pCurrTestCase = pTestCase;
	IUISystem::GetInstance().SetCurrentScreen(pTestCase->GetScreen());

	return true;
}
