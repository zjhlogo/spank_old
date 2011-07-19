/*!
 * \file GameMain.cpp
 * \date 17-05-2011 21:09:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameMain.h"
#include "OGLRenderer.h"

GameMain::GameMain()
{
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
}

GameMain::~GameMain()
{

}

GameMain& GameMain::GetInstance()
{
	static GameMain s_GameMain;
	return s_GameMain;
}

bool GameMain::Initialize(int width, int height)
{
	Terminate();

	m_nScreenWidth = width;
	m_nScreenHeight = height;
	OGLRenderer::GetInstance().Initialize(width, height);

	return true;
}

void GameMain::Terminate()
{
	OGLRenderer::GetInstance().Terminate();
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
}

void GameMain::Update(float dt)
{
	// TODO: 
}

void GameMain::Render()
{
	OGLRenderer::GetInstance().RenderTest();
}
