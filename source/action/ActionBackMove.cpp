/*!
 * \file ActionBackMove.cpp
 * \date 2011/09/16 14:54
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionBackMove.h>

ActionBackMove::ActionBackMove( uint eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fCurrTime = 0.0;
	m_fTime = time;
}

void ActionBackMove::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionBackMove::Update( float dt )
{

	if(! IsRunning()) return;

	m_fCurrTime += dt;
	// action end;
	if(m_fCurrTime > m_fTime)
	{
		SetPosition(m_vPosEnd);
		Stop();
		return;
	}
	
	SetPosition(Tween());
}

IActionBase* ActionBackMove::Clone()
{
	return new ActionBackMove(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionBackMove::CloneInverse()
{
	return new ActionBackMove(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionBackMove::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionBackMove::Tween()
{
	Vector3 pos(0.0f, 0.0f, 0.0f);
	float alpha = 0.0f;
	float  s = 1.70158f;
	switch(m_eType)
	{
	case MOVE__EASEIN:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * alpha * ((s + 1.0f) * alpha - s);
		pos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return pos;
	case  MOVE__EASEOUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha = (alpha * alpha * ((s + 1.0f) * alpha +s) + 1.0f);
		pos = alpha * (m_vPosEnd - m_vPosStart) + m_vPosStart;
		return pos;
	case  MOVE__EASEINOUT:
		s *= 1.525f;
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if(alpha < 1.0f)
		{
			alpha = (alpha * alpha * ((s  + 1.0f) * alpha - s));
			pos = alpha * (m_vPosEnd - m_vPosStart) / 2.0f + m_vPosStart;
		}
		else
		{
			alpha = alpha - 2.0f;
			alpha = (alpha * alpha * ((s + 1.0f) * alpha + s) + 2.0f);
			pos = alpha * (m_vPosEnd - m_vPosStart) /2.0f + m_vPosStart;
		}
		return pos;
	default:
		return pos;
		break;
	}
}
