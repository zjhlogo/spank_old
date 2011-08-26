/*!
 * \file GameApp.h
 * \date 7-21-2011 14:42:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

#include <IGameApp.h>
#include <msg/IMsgBase.h>
#include "TestCase.h"
#include <vector>

class GameApp : public IGameApp
{
public:
	typedef std::vector<TestCase*> TV_TEST_CASE;

public:
	GameApp();
	virtual ~GameApp();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	bool OnMsgTouch(IMsgBase* pMsg);
	bool AddTestCase(TestCase* pTestCase);

private:
	TV_TEST_CASE m_vTestCase;

	//Sprite* m_pSprite;
	//Level2D* m_pLevel;
	//SnowParticleSystem* m_pSnow;
};
#endif // __GAMEAPP_H__
