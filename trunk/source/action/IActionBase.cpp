/*!
 * \file IActionBase.cpp
 * \date 8-16-2011 10:38:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <action/IActionBase.h>
#include <msg/MsgActionUpdate.h>
#include <msg/MsgID.h>

IActionBase::IActionBase(int nID /* = 0 */)
{
	m_nID = nID;
	m_vScale = IMath::VEC3_ONE;
	m_vPosition = IMath::VEC3_ZERO;
	m_qRotation = IMath::ROT_ZERO;
	m_bRunning = false;
}

IActionBase::~IActionBase()
{
	// TODO: 
}

int IActionBase::GetID() const
{
	return m_nID;
}

const Vector3& IActionBase::GetScale() const
{
	return m_vScale;
}

void IActionBase::SetScale(const Vector3& scale)
{
	m_vScale = scale;
	// notify scale changed
	NotifyActionUpdate(AUT_SCALE);
}

void IActionBase::SetScale(float x, float y, float z)
{
	m_vScale.x = x;
	m_vScale.y = y;
	m_vScale.z = z;
	// notify scale changed
	NotifyActionUpdate(AUT_SCALE);
}

const Vector3& IActionBase::GetPosition() const
{
	return m_vPosition;
}

void IActionBase::SetPosition(const Vector3& pos)
{
	m_vPosition = pos;
	// notify position changed
	NotifyActionUpdate(AUT_POSITION);
}

void IActionBase::SetPosition(float x, float y, float z)
{
	m_vPosition.x = x;
	m_vPosition.y = y;
	m_vPosition.z = z;
	// notify position changed
	NotifyActionUpdate(AUT_POSITION);
}

const Quaternion& IActionBase::GetRotation() const
{
	return m_qRotation;
}

void IActionBase::SetRotation(const Quaternion& rot)
{
	m_qRotation = rot;
	// notify rotation changed
	NotifyActionUpdate(AUT_ROTATION);
}

void IActionBase::SetRotation(const Vector3& dir, float fRadian)
{
	m_qRotation = Quaternion(dir, fRadian);
	// notify rotation changed
	NotifyActionUpdate(AUT_ROTATION);
}

bool IActionBase::IsRunning() const
{
	return m_bRunning;
}

void IActionBase::Start()
{
	bool notify = SetRunning(true);
	if (notify)
	{
		// notify action start
		NotifyActionUpdate(AUT_START);
	}
}

void IActionBase::Stop()
{
	bool notify = SetRunning(false);
	Reset();
	if (notify)
	{
		// notify action stoped
		NotifyActionUpdate(AUT_STOPED);
	}
}

void IActionBase::Pause()
{
	bool notify = SetRunning(false);
	if (notify)
	{
		// notify action pause
		NotifyActionUpdate(AUT_PAUSE);
	}
}

void IActionBase::Restart()
{
	Stop();
	Start();
}

bool IActionBase::SetRunning(bool running)
{
	bool difference = (m_bRunning != running);
	m_bRunning = running;
	return difference;
}

void IActionBase::NotifyActionUpdate(ACTION_UPDATE_TYPE eType)
{
	MsgActionUpdate msg(eType, this);
	CallEvent(msg);
}
