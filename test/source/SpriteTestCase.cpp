/*!
 * \file SpriteTestCase.cpp
 * \date 27-08-2011 04:53:02
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "SpriteTestCase.h"
#include <ICore.h>

SpriteTestCase::SpriteTestCase()
:TestCase("SpriteTestCase")
{
	m_pSprite = NULL;
	m_pSpriteNode = NULL;
}

SpriteTestCase::~SpriteTestCase()
{
	// TODO: 
}

bool SpriteTestCase::Initialize(UIScreen* pUIScreen)
{
	m_pSpriteNode = ICore::GetInstance().GetRootNode()->CreateChildNode();
	m_pSprite = new Sprite("test_sprite.xml");
	if (!m_pSprite) return false;

	m_pSpriteNode->AttachObject(m_pSprite);

	return true;
}

void SpriteTestCase::Terminate()
{
	ICore::GetInstance().GetRootNode()->RemoveChildNode(m_pSpriteNode);
	m_pSpriteNode = NULL;
	SAFE_DELETE(m_pSprite);
}
