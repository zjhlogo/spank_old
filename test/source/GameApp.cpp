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
	return true;
}

void GameApp::Terminate()
{
	// TODO: 
}

void GameApp::Update(float dt)
{
	// TODO: 
}

void GameApp::Render()
{
	// TODO: 
}
