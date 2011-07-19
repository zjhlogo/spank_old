/*!
 * \file MsgWriter.h
 * \date 20-05-2011 00:01:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGWRITER_H__
#define __MSGWRITER_H__

#include "MsgBase.h"

class MsgWriter : public MsgBase
{
public:
	MsgWriter(int nMsgID);
	virtual ~MsgWriter();

	template <class T> bool Write(const T& t);

	virtual bool FromBuffer(StreamReader* pReader);

private:
	virtual bool Pack(StreamWriter* pWriter);
	virtual bool Unpack(StreamReader* pReader);

private:
	StreamWriter* m_pWriter;

};

template <class T> bool MsgWriter::Write(const T& t)
{
	return MsgBase::Write(t, m_pWriter);
}

#endif // __MSGWRITER_H__
