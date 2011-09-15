/*!
 * \file MsgSlider.h
 * \date 2011/09/05 16:14
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gamil.com)
 */
#ifndef __MSGSLIDER_H_
#define __MSGSLIDER_H_

#include "IMsgBaseUI.h"

class MsgSlider : public IMsgBaseUI
{
public:
	enum SILDER_TYPE
	{
		ST_UNKNOWN = 0,
		ST_CLICK,
		ST_BEGIN,
		ST_MOVE,
		ST_END,
	};

public:
	DECLARE_RTTI(MsgSlider, IMsgBaseUI);

	MsgSlider(SILDER_TYPE eType, int nCurrentPos, UIWindow* pSender);
	virtual ~MsgSlider();
	
	void SetPosition(int nCurrentPos);
	const int GetPosition() const;
	
	bool IsSilderMove() const;
	bool IsSilderBegin() const;
	bool IsSilderEnd() const;

private:
	SILDER_TYPE m_eSilderType;
	int m_nCurrentPos;

};
#endif//__MSGSLIDER_H_