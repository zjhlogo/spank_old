/*!
 * \file MsgSlider.h
 * \date 2011/09/05 16:14
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gamil.com)
 */
#ifndef __MSGSLIDER_H_
#define __MSGSLIDER_H_

#include "IMsgBase.h"
#include "../math/IMath.h"

class MsgSilder: public IMsgBase
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
	DECLARE_RTTI(MsgSilder, IMsgBase);

	MsgSilder(SILDER_TYPE eType, float fPercent);
	virtual ~MsgSilder();
	
	void SetPercent(float percent);
	const float GetPercent() const;
	
	bool IsSilderMove() const;
	bool IsSilderBegin() const;
	bool IsSilderEnd()const;
private:
	SILDER_TYPE m_eSilderType;
	float m_fPercent;

};
#endif//__MSGSLIDER_H_