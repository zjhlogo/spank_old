/*!
 * \file ActionQuadraticMove.cpp
 * \date 2011/09/16 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuadraticMove.h>

ActionQuadraticMove::ActionQuadraticMove(uint eType, const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_eType = eType;
	Reset();
}

void ActionQuadraticMove::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionQuadraticMove::Update( float dt )
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
	//
	SetPosition(Tween());
}

IActionBase* ActionQuadraticMove::Clone()
{
	return new ActionQuadraticMove(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuadraticMove::CloneInverse()
{
	return new ActionQuadraticMove(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuadraticMove::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionQuadraticMove::Tween()
{
	Vector3 pos(0.0f, 0.0f, 0.0f);
	float alpha = 0.0f;

	switch (m_eType)
	{
	case MOVE_QUADRATIC_EASEIN:
		pos = (m_vPosEnd - m_vPosStart) * ((m_fCurrTime / m_fTime) *(m_fCurrTime / m_fTime)) + m_vPosStart;
		return pos;
	case MOVE_QUADRATIC_EASEOUT:
		alpha = m_fCurrTime / m_fTime;
		pos = -(m_vPosEnd - m_vPosStart) * alpha * (alpha - 2.0f) + m_vPosStart;
		return pos;
	case MOVE_QUARTIC_EASEINOUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f) ;
		if(alpha < 1.0f)
		{
			pos = (m_vPosEnd - m_vPosStart) / 2.0f * alpha * alpha + m_vPosStart;
		}
		else
		{
			pos =  - (m_vPosEnd - m_vPosStart) / 2.0f * ((--alpha) * (alpha - 2) - 1) + m_vPosStart;
		}
		return pos;
	default:
		return Vector3(0.0, 0.0,0.0);
		break;
	}
}
