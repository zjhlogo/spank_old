/*!
 * \file MsgReader.h
 * \date 20-05-2011 00:06:36
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGREADER_H__
#define __MSGREADER_H__

#include "MsgBase.h"

class MsgReader : public MsgBase
{
public:
	MsgReader(StreamReader* pReader);
	virtual ~MsgReader();

	template <class T> bool Read(T& t);

	virtual bool ToBuffer(StreamWriter* pWriter);

private:
	virtual bool Pack(StreamWriter* pWriter);
	virtual bool Unpack(StreamReader* pReader);

private:
	StreamReader* m_pReader;

};

template <class T> bool MsgReader::Read(T& t)
{
	return MsgBase::Read(t, m_pReader);
}
#endif // __MSGREADER_H__
