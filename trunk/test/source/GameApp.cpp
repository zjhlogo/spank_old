/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"

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
	m_pSprite = ISprite::CreateSprite("test_sprite.xml");
	return true;
}

void GameApp::Terminate()
{
	SAFE_RELEASE(m_pSprite);
}

void GameApp::Update(float dt)
{
	m_pSprite->Update(dt);
}

void GameApp::Render()
{
	m_pSprite->Render();
}
