/*!
 * \file MsgDummy.cpp
 * \date 20-05-2011 23:38:52
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgDummy.h>
#include <msg/MsgID.h>

MsgDummy::MsgDummy()
:MsgBase(MI_DUMMY)
{
	m_nDummy = 0;
}

MsgDummy::MsgDummy(StreamReader* pReader)
:MsgBase(MI_DUMMY)
{
	FromBuffer(pReader);
}

MsgDummy::~MsgDummy()
{

}

MsgBase* MsgDummy::CreateInstance()
{
	return new MsgDummy();
}

bool MsgDummy::Pack(StreamWriter* pWriter)
{
	Write(m_nDummy, pWriter);
	return true;
}

bool MsgDummy::Unpack(StreamReader* pReader)
{
	Read(m_nDummy, pReader);
	return true;
}
