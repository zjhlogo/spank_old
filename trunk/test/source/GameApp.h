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
#include <ITexture.h>
#include <ISprite.h>
#include <math/IMath.h>

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
	Matrix4x4 m_matRot;
	ISprite* m_pSprite;

};
#endif // __GAMEAPP_H__
