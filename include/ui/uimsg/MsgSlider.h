/*!
 * \file MsgSlider.h
 * \date 2011/09/05 16:14
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gamil.com)
 */
#ifndef __MSGSLIDER_H__
#define __MSGSLIDER_H__

#include "IMsgBaseUI.h"

class MsgSlider : public IMsgBaseUI
{
public:
	enum SLIDER_TYPE
	{
		ST_POSITION,
		ST_TRACKING,
	};

public:
	DECLARE_RTTI(MsgSlider, IMsgBaseUI);

	MsgSlider(SLIDER_TYPE eType, int nPos, UIWindow* pSender);
	virtual ~MsgSlider();
	
	void SetPosition(int nCurrentPos);
	int GetPosition() const;
	
	bool IsPositionChanged() const;
	bool IsTracking() const;

private:
	SLIDER_TYPE m_eSliderType;
	int m_nPos;

};
#endif // __MSGSLIDER_H__
