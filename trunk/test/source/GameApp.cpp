/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"
#include <util/IDebugUtil.h>
#include <msg/MsgID.h>
#include <msg/MsgMgr.h>
#include <msg/MsgTouchEvent.h>
#include <ICore.h>

IGameApp& IGameApp::GetInstance()
{
	static GameApp s_GameApp;
	return s_GameApp;
}

GameApp::GameApp()
{
	// TODO: 
}

GameApp::~GameApp()
{
	// TODO: 
}

bool GameApp::Initialize()
{
	MsgMgr::GetInstance().SubscribeMessage(MI_TOUCH_EVENT, this, (MSG_CALLBACK)&GameApp::OnTouchEvent);

	m_Level2D = ILevel2D::CreateLevel2D("test.xml");
	m_pSprite = new Sprite("test_sprite.xml");
	INode* pRootNode = ICore::GetInstance().GetRootNode();
	pRootNode->AttachObject(m_Level2D);
	pRootNode->SetPosition(0.0f,0.0f,0.0f);
	INode* Level2DNode = pRootNode->CreateChildNode();
	Level2DNode->AttachObject(m_pSprite);
	return true;
}

void GameApp::Terminate()
{
	SAFE_DELETE(m_pSprite);
	SAFE_RELEASE(m_Level2D);
}

void GameApp::Update(float dt)
{
	//m_pSprite->Update(dt);
	//m_Level2D->Update(dt);
}

void GameApp::Render()
{
	//m_Level2D->Render();
	//m_pSprite->Render();
}

bool GameApp::OnTouchEvent(uint nMsgID, IMsgBase* pMsg)
{
	MsgTouchEvent* pTouchEvent = (MsgTouchEvent*)pMsg;

	if (pTouchEvent->IsTouchBegin())
	{
		LOGD("touch begin: (%.02f, %.02f)", pTouchEvent->GetPosition().x, pTouchEvent->GetPosition().y);
	}
	else if (pTouchEvent->IsTouchMove())
	{
		LOGD("touch move: (%.02f, %.02f)", pTouchEvent->GetPosition().x, pTouchEvent->GetPosition().y);
	}
	else if (pTouchEvent->IsTouchEnd())
	{
		LOGD("touch end: (%.02f, %.02f)", pTouchEvent->GetPosition().x, pTouchEvent->GetPosition().y);
	}

	return true;
}
