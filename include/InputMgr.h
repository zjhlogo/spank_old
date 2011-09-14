/*!
 * \file InputMgr.h
 * \date 8-10-2011 14:19:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __INPUTMGR_H__
#define __INPUTMGR_H__

#include "IMgr.h"

class InputMgr : public IMgr
{
public:
	enum CONST_DEFINE
	{
		MAX_TOUCH_SUPPORT = 4,
	};

public:
	DECLARE_RTTI(InputMgr, IMgr);

	InputMgr();
	virtual ~InputMgr();

	static InputMgr& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	void OnTouchStart(int nIndex, float x, float y);
	void OnTouchMove(int nIndex, float x, float y);
	void OnTouchEnd(int nIndex, float x, float y);

private:
	bool m_bTouchDown[MAX_TOUCH_SUPPORT];

};
#endif // __INPUTMGR_H__
