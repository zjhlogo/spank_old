/*!
 * \file IGameMain.cpp
 * \date 7-20-2011 17:47:53
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IGameMain.h>
#include <IRenderer.h>

IGameMain::IGameMain()
{
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
}

IGameMain::~IGameMain()
{
	Terminate();
}

bool IGameMain::Initialize(int width, int height)
{
	Terminate();

	m_nScreenWidth = width;
	m_nScreenHeight = height;

	IRenderer::GetInstance().Initialize(width, height);

	return true;
}

void IGameMain::Terminate()
{
	IRenderer::GetInstance().Terminate();
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
}
