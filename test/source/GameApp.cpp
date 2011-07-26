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
	m_pShader = NULL;
	m_matOrtho.MakeIdentity();
}

GameApp::~GameApp()
{
	// TODO: 
}

bool GameApp::Initialize()
{
	static const IVertexAttribute::ATTRIBUTE_ITEM s_VertAttrs[] = 
	{
		{3, IVertexAttribute::AT_FLOAT, 0, "a_position"},
		{2, IVertexAttribute::AT_FLOAT, 0, "a_texCoord"},
		{0, IVertexAttribute::AT_UNKNOWN, 0, ""},
	};

	m_pTexture = ITextureMgr::GetInstance().CreateTexture("emotion_small.png");
	m_pShader = IShaderMgr::GetInstance().CreateShaderFromFiles("shader.vs", "shader.fs", s_VertAttrs);
	m_matOrtho.MakeOrtho(-400.0f, 400.0f, -240.0f, 240.0f, 100.0f, -100.0f);
	return true;
}

void GameApp::Terminate()
{
	SAFE_RELEASE(m_pShader);
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

	m_pShader->SetMatrix4x4("u_project", &m_matOrtho);
	m_pShader->SetTexture("s_texture", m_pTexture);
	IRenderer2D::GetInstance().SetShader(m_pShader);
	IRenderer2D::GetInstance().DrawTriangleList(s_Verts, 6);
}
