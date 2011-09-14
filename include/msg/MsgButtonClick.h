/*!
 * \file MsgButtonClick.h
 * \date 2011/09/14 17:16
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#ifndef __MSGBUTTONCLICK_H_
#define __MSGBUTTONCLICK_H_
#include "msg/IMsgBase.h"
#include "../math/IMath.h"
class MsgButtonClick : public IMsgBase
{
public:
	enum BUTTON_CLICK_TYPE
	{
		BCT_CHECK = 0,
		BCT_CHECK_PRESSED,
		BCT_CHECK_DISABLED,
		BCT_UNCHECK,
		BCT_UNCHECK_PRESSED,
		BCT_UNCHECK_DISABLED,
	};
public:
	DECLARE_RTTI(MsgButtonClick, IMsgBase);

	MsgButtonClick(BUTTON_CLICK_TYPE eType, const Vector2& Pos);
	MsgButtonClick(BUTTON_CLICK_TYPE eType, float x, float y);
	~MsgButtonClick();

	void SetPosition( const Vector2& Pos);
	void SetPosition(float x, float y);
	const Vector2& GetPosition() const;

private:
	
	BUTTON_CLICK_TYPE m_eType;
	Vector2 m_vPosition;
};
#endif//__MSGBUTTONCLICK_H_
