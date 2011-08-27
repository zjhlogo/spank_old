/*!
 * \file MapTestCase.cpp
 * \date 27-08-2011 05:30:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "MapTestCase.h"

MapTestCase::MapTestCase()
:TestCase("MapTestCase")
{
	m_pLevel = NULL;
}

MapTestCase::~MapTestCase()
{
	// TODO: 
}

bool MapTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pLevel = new Level2D("level.l2d");
	if (!m_pLevel || !m_pLevel->IsOK()) return false;

	m_vSpeed = Vector2(40.0f, 50.0f);
	m_vPosition = IMath::VEC2_ZERO;

	return true;
}

void MapTestCase::Terminate()
{
	SAFE_DELETE(m_pLevel);
}

void MapTestCase::Update(float dt)
{
	m_vPosition += m_vSpeed * dt;
	m_pLevel->SetCenterPosition(m_vPosition);
	m_pLevel->Update(dt);

	if (m_vPosition.x < -2400.0f || m_vPosition.x > 2400.0f) m_vSpeed.x = -m_vSpeed.x;
	if (m_vPosition.y < -2400.0f || m_vPosition.y > 2400.0f) m_vSpeed.y = -m_vSpeed.y;
}

void MapTestCase::Render()
{
	m_pLevel->Render();
}
