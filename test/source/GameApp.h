/*!
 * \file GameApp.h
 * \date 7-21-2011 14:42:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __GAMEAPP_H__
#define __GAMEAPP_H__

#include <IGameMain.h>
#include <ITexture.h>

class GameApp : public IGameMain
{
public:
	GameApp();
	virtual ~GameApp();

	virtual void Update(float dt);
	virtual void Render();

private:
	ITexture* m_pTexture;

};
#endif // __GAMEAPP_H__
