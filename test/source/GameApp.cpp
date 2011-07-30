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
#include <string.h>

IGameApp& IGameApp::GetInstance()
{
	static GameApp s_GameApp;
	return s_GameApp;
}

GameApp::GameApp()
{
	m_nIndex = 0;
	memset(m_pTexture, 0, sizeof(m_pTexture));
}

GameApp::~GameApp()
{
	// TODO: 
}

bool GameApp::Initialize()
{
	m_pTexture[0] = ITextureMgr::GetInstance().CreateTexture("big_bodyguard.png");
	m_pTexture[1] = ITextureMgr::GetInstance().CreateTexture("big_cellphone.png");
	m_pTexture[2] = ITextureMgr::GetInstance().CreateTexture("big_cigarette.png");
	m_pTexture[3] = ITextureMgr::GetInstance().CreateTexture("big_coffee.png");
	m_pTexture[4] = ITextureMgr::GetInstance().CreateTexture("big_mixeddrink.png");
	m_pTexture[5] = ITextureMgr::GetInstance().CreateTexture("big_racingcar.png");
	return true;
}

void GameApp::Terminate()
{
	for (int i = 0; i < 6; ++i)
	{
		SAFE_RELEASE(m_pTexture[i]);
	}
}

void GameApp::Update(float dt)
{
	static float s_fTotalTime = 0.0f;
	s_fTotalTime += dt;

	IMath::BuildRotateMatrixZ(m_matRot, s_fTotalTime);
}

void GameApp::Render()
{
	float width = (float)m_pTexture[m_nIndex]->GetWidth();
	float height = (float)m_pTexture[m_nIndex]->GetHeight();

	Matrix4x4 matResult = IRenderer2D::GetInstance().GetProjectionMatrix() * m_matRot;
	matResult.Transport();
	IRenderer2D::GetInstance().SetMatrix(&matResult);
	IRenderer2D::GetInstance().SetTexture(m_pTexture[m_nIndex]);
	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, width, height);
}
