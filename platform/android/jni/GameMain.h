/*!
 * \file GameMain.h
 * \date 17-05-2011 21:07:31
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __GAMEMAIN_H__
#define __GAMEMAIN_H__

#include "MessageHandler.h"

class GameMain : public MessageHandler
{
public:
	static GameMain& GetInstance();

	bool Initialize(int width, int height);
	void Terminate();

	void Update(float dt);
	void Render();

private:
	GameMain();
	virtual ~GameMain();

private:
	int m_nScreenWidth;
	int m_nScreenHeight;

};
#endif // __GAMEMAIN_H__
