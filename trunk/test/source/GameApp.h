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
#include <Sprite.h>
#include <Level2D.h>
#include <particle/SnowParticleSystem.h>
#include <ui/UIString.h>

class GameApp : public IGameApp
{
public:
	GameApp();
	virtual ~GameApp();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void Update(float dt);
	virtual void Render();

private:
	bool OnMsgTouch(IMsgBase* pMsg);

private:
	Sprite* m_pSprite;
	Level2D* m_pLevel;
	SnowParticleSystem* m_pSnow;

	UIString* m_pString;
	IFont* m_pFont;

};
#endif // __GAMEAPP_H__
