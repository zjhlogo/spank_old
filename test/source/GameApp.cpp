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
#include <msg/MsgTouch.h>
#include <action/ActionMoveTo.h>
#include <action/ActionSequeue.h>
#include <action/ActionLoop.h>
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
	MsgMgr::GetInstance().SubscribeMessage(MI_TOUCH, this, (MSG_CALLBACK)&GameApp::OnMsgTouch);

	m_pLevel = ILevel2D::CreateLevel2D("test.xml");
	INode* pRootNode = ICore::GetInstance().GetRootNode();
	pRootNode->AttachObject(m_pLevel);

	INode* pSpriteNode = pRootNode->CreateChildNode();
	m_pSprite = new Sprite("test_sprite.xml");
	pSpriteNode->AttachObject(m_pSprite);

	ActionSequeue* pActionSequeue = new ActionSequeue();
	IActionBase* pActMoveTo = new ActionMoveTo(IMath::VEC3_ZERO, Vector3(200.0f, 0.0f, 0.0f), 2.0f);
	pActionSequeue->AddAction(pActMoveTo);
	pActionSequeue->AddAction(pActMoveTo->CloneInverse());
	ActionLoop * pActionLoop = new ActionLoop(pActionSequeue, 1);

	pSpriteNode->RunAction(pActionLoop);

	return true;
}

void GameApp::Terminate()
{
	SAFE_DELETE(m_pSprite);
	SAFE_RELEASE(m_pLevel);
}

void GameApp::Update(float dt)
{
	//static Vector2 s_posCenter(0.0f, 0.0f);

	//s_posCenter.x += (dt*50.0f);
	//m_pLevel2D->SetCenterPosition(s_posCenter);
}

void GameApp::Render()
{
	// TODO: 
}

bool GameApp::OnMsgTouch(IMsgBase* pMsg)
{
	MsgTouch* pMsgTouch = (MsgTouch*)pMsg;

	if (pMsgTouch->IsTouchBegin())
	{
		LOGD("touch begin: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
	}
	else if (pMsgTouch->IsTouchMove())
	{
		LOGD("touch move: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
	}
	else if (pMsgTouch->IsTouchEnd())
	{
		LOGD("touch end: (%.02f, %.02f)", pMsgTouch->GetPosition().x, pMsgTouch->GetPosition().y);
	}

	return true;
}
