/*!
 * \file MsgCommon.cpp
 * \date 8-16-2011 13:59:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgCommon.h>
#include <msg/MsgID.h>

MsgCommon::MsgCommon(uint nMsgID)
:IMsgBase(nMsgID)
{
	m_nData = 0;
	m_pData = NULL;
	m_pObject = NULL;
}

MsgCommon::~MsgCommon()
{
	// TODO: 
}

uint MsgCommon::GetData() const
{
	return m_nData;
}

void MsgCommon::SetData(uint nData)
{
	m_nData = nData;
}

void* MsgCommon::GetDataPtr() const
{
	return m_pData;
}

void MsgCommon::SetDataPtr(void* pData)
{
	m_pData = pData;
}

IObject* MsgCommon::GetObject() const
{
	return m_pObject;
}

void MsgCommon::SetObject(IObject* pObject)
{
	m_pObject = pObject;
}
