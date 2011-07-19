/*!
 * \file MsgDummy.h
 * \date 20-05-2011 23:37:19
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGDUMMY_H__
#define __MSGDUMMY_H__

#include "MsgBase.h"

class MsgDummy : public MsgBase
{
public:
	MsgDummy();
	MsgDummy(StreamReader* pReader);
	virtual ~MsgDummy();

	virtual MsgBase* CreateInstance();

private:
	virtual bool Pack(StreamWriter* pWriter);
	virtual bool Unpack(StreamReader* pReader);

private:
	int m_nDummy;

};
#endif // __MSGDUMMY_H__