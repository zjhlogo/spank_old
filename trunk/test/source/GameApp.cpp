/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"
#include <IRenderer.h>
#include <ITextureMgr.h>

IGameMain& IGameMain::GetInstance()
{
	static GameApp s_GameApp;
	return s_GameApp;
}

GameApp::GameApp()
{
	// TODO: 
	m_pTexture = NULL;
}

GameApp::~GameApp()
{
	// TODO: 
}

void GameApp::Update(float dt)
{
	if (!m_pTexture)
	{
		m_pTexture = ITextureMgr::GetInstance().CreateTexture("assets/emotion_small.png");
	}
}

void GameApp::Render()
{
	IRenderer::GetInstance().RenderTest();
}
