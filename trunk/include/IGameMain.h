/*!
 * \file IGameMain.h
 * \date 7-20-2011 17:46:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IGAMEMAIN_H__
#define __IGAMEMAIN_H__

#include "BaseType.h"

class IGameMain
{
public:
	IGameMain();
	virtual ~IGameMain();

	static IGameMain& GetInstance();

	virtual bool Initialize(int width, int height);
	virtual void Terminate();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

private:
	int m_nScreenWidth;
	int m_nScreenHeight;

};
#endif // __IGAMEMAIN_H__
