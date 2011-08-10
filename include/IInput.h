/*!
 * \file IInput.h
 * \date 8-09-2011 17:49:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IINPUT_H__
#define __IINPUT_H__

#include "IMgr.h"

class IInput : public IMgr
{
public:
	enum CONST_DEFINE
	{
		MAX_TOUCHES_SUPPORT = 4,
	};

public:
	static IInput& GetInstance();

	virtual void OnTouchStart(int nIndex, float x, float y) = 0;
	virtual void OnTouch(int nIndex, float x, float y) = 0;
	virtual void OnTouchEnd(int nIndex, float x, float y) = 0;

	virtual void DispatchTouchEvents() = 0;

};
#endif // __IINPUT_H__
