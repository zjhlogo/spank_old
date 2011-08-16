/*!
 * \file MsgActionUpdate.h
 * \date 8-16-2011 11:43:30
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __MSGACTIONUPDATE_H__
#define __MSGACTIONUPDATE_H__

#include "IMsgBase.h"
#include "../action/IActionBase.h"

class MsgActionUpdate : public IMsgBase
{
public:
	MsgActionUpdate(ACTION_UPDATE_TYPE eType, IActionBase* pAction);
	virtual ~MsgActionUpdate();

	int GetActionID() const;
	ACTION_UPDATE_TYPE GetUpdateType() const;

	const Vector3& GetScale() const;
	const Vector3& GetPosition() const;
	const Quaternion& GetRotation() const;

	IActionBase* GetAction();

private:
	ACTION_UPDATE_TYPE m_eType;
	IActionBase* m_pAction;

};
#endif // __MSGACTIONUPDATE_H__
