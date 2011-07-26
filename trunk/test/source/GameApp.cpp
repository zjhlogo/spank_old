/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"
#include <ITextureMgr.h>
#include <IShaderMgr.h>
#include <IRenderer2D.h>

IGameApp& IGameApp::GetInstance()
{
	static GameApp s_GameApp;
	return s_GameApp;
}

GameApp::GameApp()
{
	m_pTexture = NULL;
}

GameApp::~GameApp()
{
	// TODO: 
}

bool GameApp::Initialize()
{
	m_pTexture = ITextureMgr::GetInstance().CreateTexture("emotion_small.png");
	return true;
}

void GameApp::Terminate()
{
	SAFE_RELEASE(m_pTexture);
}

void GameApp::Update(float dt)
{
	// TODO: 
}

void GameApp::Render()
{
	static const float s_Verts[] =
	{
		-200.0f,  200.0f, 0.0f, 0.0f, 1.0f,
		-200.0f, -200.0f, 0.0f, 0.0f, 0.0f,
		 200.0f, -200.0f, 0.0f, 1.0f, 0.0f,

		-200.0f,  200.0f, 0.0f, 0.0f, 1.0f,
		 200.0f, -200.0f, 0.0f, 1.0f, 0.0f,
		 200.0f,  200.0f, 0.0f, 1.0f, 1.0f,
	};
	//static const float s_Verts[] =
	//{
	//	 0.0f,   0.2f,  -0.2f, 0.5f, 1.0f,
	//	-0.1f,  -0.2f,  -0.2f, 0.0f, 0.0f,
	//	 0.1f,  -0.2f,  -0.2f, 1.0f, 0.0f,
	//};

	IRenderer2D::GetInstance().SetTexture(m_pTexture);
	IRenderer2D::GetInstance().DrawTriangleList(s_Verts, 6);
}
