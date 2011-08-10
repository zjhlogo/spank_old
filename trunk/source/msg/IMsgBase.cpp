/*!
 * \file IMsgBase.cpp
 * \date 8-10-2011 14:03:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/IMsgBase.h>

IMsgBase::IMsgBase(uint nMsgID)
{
	m_nMsgID = nMsgID;
}

IMsgBase::~IMsgBase()
{
	// TODO: 
}

uint IMsgBase::GetMsgID() const
{
	return m_nMsgID;
}
