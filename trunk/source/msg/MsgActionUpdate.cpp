/*!
 * \file MsgActionUpdate.cpp
 * \date 8-16-2011 11:43:34
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <msg/MsgActionUpdate.h>
#include <msg/MsgID.h>

MsgActionUpdate::MsgActionUpdate(ACTION_UPDATE_TYPE eType, IActionBase* pAction)
:IMsgBase(MI_ACTION_UPDATE)
{
	m_eType = eType;
	m_pAction = pAction;
}

MsgActionUpdate::~MsgActionUpdate()
{
	// TODO: 
}

int MsgActionUpdate::GetActionID() const
{
	return m_pAction->GetID();
}

ACTION_UPDATE_TYPE MsgActionUpdate::GetUpdateType() const
{
	return m_eType;
}

const Vector3& MsgActionUpdate::GetScale() const
{
	return m_pAction->GetScale();
}

const Vector3& MsgActionUpdate::GetPosition() const
{
	return m_pAction->GetPosition();
}

const Quaternion& MsgActionUpdate::GetRotation() const
{
	return m_pAction->GetRotation();
}

IActionBase* MsgActionUpdate::GetAction()
{
	return m_pAction;
}
