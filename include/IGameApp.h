/*!
 * \file IGameApp.h
 * \date 24-07-2011 11:21:06
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IGAMEAPP_H__
#define __IGAMEAPP_H__

#include "BaseType.h"
#include "IMgr.h"

class IGameApp : public IMgr
{
public:
	DECLARE_RTTI(IGameApp, IMgr);

	static IGameApp& GetInstance();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

};
#endif // __IGAMEAPP_H__
