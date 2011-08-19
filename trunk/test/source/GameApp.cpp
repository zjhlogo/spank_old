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
#include <action/ActionRotateTo.h>
#include <action/ActionScaleTo.h>
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

	m_pLevel = new Level2D("OUT.L2D");
	INode* pRootNode = ICore::GetInstance().GetRootNode();
	pRootNode->AttachObject(m_pLevel);

	INode* pSpriteNode = pRootNode->CreateChildNode();
	m_pSprite = new Sprite("test_sprite.xml");
	pSpriteNode->AttachObject(m_pSprite);

	ActionSequeue* pActionSequeue = new ActionSequeue();
	//IActionBase* pActMoveTo1 = new ActionMoveTo(Vector3(0.0f, 0.0f, 0.0f), Vector3(200.0f, 0.0f, 0.0f), 2.0f);
	//IActionBase* pActMoveTo2 = new ActionMoveTo(Vector3(200.0f, 0.0f, 0.0f), Vector3(200.0f, 200.0f, 0.0f), 2.0f);
	//IActionBase* pActMoveTo3 = new ActionMoveTo(Vector3(200.0f, 200.0f, 0.0f), Vector3(0.0f, 200.0f, 0.0f), 2.0f);
	//IActionBase* pActMoveTo4 = new ActionMoveTo(Vector3(0.0f, 200.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f), 2.0f);
	IActionBase* pActMoveTo1 = new ActionScaleTo(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.8f, 0.8f, 0.8f), 10.0f);
	IActionBase* pActMoveTo2 = new ActionScaleTo(Vector3(0.8f, 0.8f, 0.8f), Vector3(0.6f, 0.6f, 0.6f), 10.0f);
	IActionBase* pActMoveTo3 = new ActionScaleTo(Vector3(0.6f, 0.6f, 0.6f), Vector3(0.4f, 0.4f, 0.4f), 10.0f);
	IActionBase* pActMoveTo4 = new ActionScaleTo(Vector3(0.4f, 0.4f, 0.4f), Vector3(0.6f, 0.6f, 0.6f), 10.0f);
	IActionBase* pActMoveTo5 = new ActionScaleTo(Vector3(0.6f, 0.6f, 0.6f), Vector3(0.8f, 0.8f, 0.8f), 10.0f);
	IActionBase* pActMoveTo6 = new ActionScaleTo(Vector3(0.8f, 0.8f, 0.8f), Vector3(1.0f, 1.0f, 1.0f), 10.0f);

	pActionSequeue->AddAction(pActMoveTo1);
	pActionSequeue->AddAction(pActMoveTo2);
	pActionSequeue->AddAction(pActMoveTo3);
	pActionSequeue->AddAction(pActMoveTo4);
	pActionSequeue->AddAction(pActMoveTo5);
	pActionSequeue->AddAction(pActMoveTo6);
	ActionLoop * pActionLoop = new ActionLoop(pActionSequeue);

	pSpriteNode->RunAction(pActionLoop);
	
	m_pSnow = new SnowParticleSystem();

	return true;
}

void GameApp::Terminate()
{
	SAFE_DELETE(m_pSprite);
	SAFE_RELEASE(m_pLevel);
	SAFE_DELETE(m_pSnow);
}

void GameApp::Update(float dt)
{
	//const Vector3& pos = m_pSprite->GetParentNode()->GetPosition();
	static Vector2 positon(0,0);
	positon.x -= 40*dt;
	positon.y -= 40*dt;
	m_pLevel->SetCenterPosition(positon);
	m_pSnow->Update(dt);
}

void GameApp::Render()
{
	// TODO: 
	m_pSnow->Render();
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
