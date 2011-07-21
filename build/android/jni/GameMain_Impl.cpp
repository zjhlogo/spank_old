/*!
 * \file GameMain_Impl.cpp
 * \date 7-20-2011 17:51:12
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "GameMain_Impl.h"
#include <IRenderer.h>

IGameMain& IGameMain::GetInstance()
{
	static GameMain_Impl s_GameMain;
	return s_GameMain;
}

GameMain_Impl::GameMain_Impl()
{
	// TODO: 
}

GameMain_Impl::~GameMain_Impl()
{
	// TODO: 
}

void GameMain_Impl::Update(float dt)
{
	// TODO: 
}

void GameMain_Impl::Render()
{
	IRenderer::GetInstance().RenderTest();
}
