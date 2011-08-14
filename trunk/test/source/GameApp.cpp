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

	m_pSprite = new Sprite("test_sprite.xml");
	INode* pRootNode = ICore::GetInstance().GetRootNode();
	pRootNode->AttachObject(m_pSprite);
	pRootNode->SetPosition(200.0f, 100.0f, 0.0f);
	pRootNode->SetRotation(IMath::VEC3_AXISZ, IMath::F_PI/4.0f);
	pRootNode->SetScale(1.5f, 1.5f, 0.5f);

	return true;
}

void GameApp::Terminate()
{
	SAFE_DELETE(m_pSprite);
}

void GameApp::Update(float dt)
{
}

void GameApp::Render()
{
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
