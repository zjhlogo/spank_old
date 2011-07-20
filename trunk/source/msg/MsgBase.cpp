/*!
 * \file MsgBase.cpp
 * \date 18-05-2011 23:10:24
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgBase.h>

MsgBase::MsgBase(int nID)
:m_nID(nID)
{
	// TODO: 
}

MsgBase::~MsgBase()
{
	// TODO: 
}

int MsgBase::GetID()
{
	return m_nID;
}

bool MsgBase::ToBuffer(StreamWriter* pWriter)
{
	if (!WriteBaseData(pWriter)) return false;
	if (!Pack(pWriter)) return false;
	return true;
}

bool MsgBase::FromBuffer(StreamReader* pReader)
{
	if (!ReadBaseData(pReader)) return false;
	if (!Unpack(pReader)) return false;
	return true;
}

bool MsgBase::WriteBaseData(StreamWriter* pWriter)
{
	return Write(m_nID, pWriter);
}

bool MsgBase::ReadBaseData(StreamReader* pReader)
{
	return Read(m_nID, pReader);
}
