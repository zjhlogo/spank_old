/*!
 * \file GameMain_Impl.h
 * \date 7-20-2011 17:50:28
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __GAMEMAIN_IMPL_H__
#define __GAMEMAIN_IMPL_H__

#include <IGameMain.h>

class GameMain_Impl : public IGameMain
{
public:
	GameMain_Impl();
	virtual ~GameMain_Impl();

	virtual void Update(float dt);
	virtual void Render();

};
#endif // __GAMEMAIN_IMPL_H__
