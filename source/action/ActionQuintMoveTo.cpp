/*!
 * \file ActionQuintMoveTo.cpp
 * \date 2011/09/16 17:53
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuintMoveTo.h>

ActionQuintMoveTo::ActionQuintMoveTo( MOVE_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;
}

ActionQuintMoveTo::~ActionQuintMoveTo()
{
	//TODO:
}

void ActionQuintMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionQuintMoveTo::Update( float dt )
{
	if(!IsRunning()) return;

	m_fCurrTime += dt;
	if( m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}

	SetPosition(Tween());
}

IActionBase* ActionQuintMoveTo::Clone()
{
	return new ActionQuintMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuintMoveTo::CloneInverse()
{
	return new ActionQuintMoveTo (m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuintMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionQuintMoveTo::Tween()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);
	//TODO:

	return vPos;
}
