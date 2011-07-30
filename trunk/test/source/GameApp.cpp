/*!
 * \file GameApp.cpp
 * \date 7-21-2011 14:42:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameApp.h"
#include <ITextureMgr.h>
#include <IRenderer2D.h>
#include <string.h>

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
	//static float s_fTotalTime = 0.0f;
	//s_fTotalTime += dt;

	//IMath::BuildRotateMatrixZ(m_matRot, s_fTotalTime);
	//m_matRot.SetTranslate(100.0f, 100.0f, 0.0f);
	m_pSprite->Update(dt);
}

void GameApp::Render()
{
	Matrix4x4 matResult = IRenderer2D::GetInstance().GetProjectionMatrix()/* * m_matRot*/;
	matResult.Transport();
	IRenderer2D::GetInstance().SetMatrix(&matResult);
	m_pSprite->Render();
	//IRenderer2D::GetInstance().SetTexture(m_pTexture[m_nIndex]);
	//IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, width, height);
}
