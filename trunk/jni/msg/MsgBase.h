/*!
 * \file MsgBase.h
 * \date 18-05-2011 23:05:56
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGBASE_H__
#define __MSGBASE_H__

#include "../util/StreamWriter.h"
#include "../util/StreamReader.h"

class MsgBase
{
public:
	MsgBase(int nID);
	virtual ~MsgBase();

	int GetID();

	virtual bool ToBuffer(StreamWriter* pWriter);
	virtual bool FromBuffer(StreamReader* pReader);

protected:
	template <class T> bool Write(const T& t, StreamWriter* pWriter);
	template <class T> bool Read(T& t, StreamReader* pReader);

	bool WriteBaseData(StreamWriter* pWriter);
	bool ReadBaseData(StreamReader* pReader);

	virtual bool Pack(StreamWriter* pWriter) = 0;
	virtual bool Unpack(StreamReader* pReader) = 0;

private:
	int m_nID;			// see enum MESSAGE_ID

};

template <class T> bool MsgBase::Write(const T& t, StreamWriter* pWriter)
{
	if (!pWriter) return false;

	return pWriter->Write(&t, sizeof(t));
}

template <class T> bool MsgBase::Read(T& t, StreamReader* pReader)
{
	if (!pReader) return false;

	return pReader->Read(&t, sizeof(t));
}

#endif // __MSGBASE_H__
