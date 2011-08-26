/*!
 * \file TestCase.cpp
 * \date 8-25-2011 9:29:39
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "TestCase.h"
#include <ui/IUISystem.h>

TestCase::TestCase(const char* pszTestName)
{
	if (!pszTestName)
	{
		m_strTestName = pszTestName;
	}
	else
	{
		m_strTestName = "Unknown";
	}

	m_pUIScreen = NULL;
}

TestCase::~TestCase()
{
	// TODO: 
}

bool TestCase::InternalInitialize()
{
	m_pUIScreen = IUISystem::GetInstance().CreateUIScreen();
	if (!m_pUIScreen) return false;

	if (!Initialize(m_pUIScreen)) return false;
	AddReturnButton(m_pUIScreen);

	return true;
}

void TestCase::InternalTerminate()
{
	Terminate();

	IUISystem::GetInstance().ReleaseUIScreen(m_pUIScreen);
	m_pUIScreen = NULL;
}

void TestCase::Update(float dt)
{
	// TODO: 
}

void TestCase::Render()
{
	// TODO: 
}

void TestCase::AddReturnButton(UIScreen* pUIScreen)
{
	// TODO: 
}
