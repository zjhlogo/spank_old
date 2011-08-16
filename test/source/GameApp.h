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
#include <Sprite.h>
#include <msg/IMsgBase.h>
#include <ILevel2D.h>

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
	bool OnTouchEvent(uint nMsgID, IMsgBase* pMsg);
	ILevel2D* m_Level2D;
private:
	Sprite* m_pSprite;

};
#endif // __GAMEAPP_H__
