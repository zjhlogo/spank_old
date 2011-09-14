/*!
 * \file Box2DTestCase.cpp
 * \date 8-30-2011 16:21:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Box2DTestCase.h"
#include <IRenderer2D.h>
#include <IShaderMgr.h>
#include <IResourceMgr.h>

Box2DTestCase::Box2DTestCase()
:TestCase("Box2DTestCase")
{
	m_pWorld = NULL;
	m_pBody = NULL;
	m_pShader = NULL;
	m_pBoxPiece = NULL;
}

Box2DTestCase::~Box2DTestCase()
{
	// TODO: 
}

bool Box2DTestCase::Initialize(UIScreen* pUIScreen)
{
	b2Vec2 gravity(0.0f, -9.8f);
	m_pWorld = new b2World(gravity, true);

	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);
	b2Body* groundBody = m_pWorld->CreateBody(&groundBodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 5.0f);
	groundBody->CreateFixture(&groundBox, 0.0f);

	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0.0f, 4.0f);
	m_pBody = m_pWorld->CreateBody(&bodyDef);

	b2PolygonShape dynamicBox;
	dynamicBox.SetAsBox(1.0f, 1.0f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &dynamicBox;
	fixtureDef.density = 1.0f;
	fixtureDef.friction = 0.3f;
	m_pBody->CreateFixture(&fixtureDef);

	m_pShader = IShaderMgr::GetInstance().CreateShader(SSI_DEFAULT);
	if (!m_pShader) return false;

	m_pBoxPiece = IResourceMgr::GetInstance().FindImagePiece("ui_slider_thumb");
	if (!m_pBoxPiece) return false;

	return true;
}

void Box2DTestCase::Terminate()
{
	SAFE_DELETE(m_pWorld);
	m_pBody = NULL;
	SAFE_RELEASE(m_pShader);
}

void Box2DTestCase::Update(float dt)
{
	m_pWorld->Step(dt, 10, 10);
	m_pWorld->ClearForces();
}

void Box2DTestCase::Render()
{
	const b2Vec2& pos = m_pBody->GetPosition();
	float fRadian = m_pBody->GetAngle();

	Matrix4x4 matModelView;
	IMath::BuildRotateMatrixZ(matModelView, fRadian);
	matModelView.SetTranslate(pos.x*50.0f, pos.y*50.0f, 0.0f);

	IRenderer2D::GetInstance().SetModelViewMatrix(matModelView);

	m_pShader->SetMatrix4x4("u_matModelViewProj", IRenderer2D::GetInstance().GetFinalMatrixTranspose());
	m_pShader->SetTexture("u_texture", m_pBoxPiece->pTexture);
	IRenderer2D::GetInstance().DrawRect(0.0f, 0.0f, m_pBoxPiece, m_pShader);
}
