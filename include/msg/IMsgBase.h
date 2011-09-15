/*!
 * \file IMsgBase.h
 * \date 8-10-2011 11:37:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IMSGBASE_H__
#define __IMSGBASE_H__

#include "../IRtti.h"

class IMsgBase
{
public:
	DECLARE_RTTI(IMsgBase, INoRtti);

	IMsgBase(uint nMsgID);
	virtual ~IMsgBase();

	uint GetMsgID() const;

private:
	uint m_nMsgID;

};
#endif // __IMSGBASE_H__
