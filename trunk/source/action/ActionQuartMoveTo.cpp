/*!
 * \file ActionQuartMoveTo.cpp
 * \date 2011/09/16 17:35
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuartMoveTo.h>

ActionQuartMoveTo::ActionQuartMoveTo( MOVE_TYPE eType,const Vector3& posStart, const Vector3& posEnd, float time )
{
	
	m_eType = eType;
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_fCurrTime = 0.0f;
}

ActionQuartMoveTo::~ActionQuartMoveTo()
{
	//TODO:
}

void ActionQuartMoveTo::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionQuartMoveTo::Update( float dt )
{
	//TODO:
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

IActionBase* ActionQuartMoveTo::Clone()
{
	return new ActionQuartMoveTo(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuartMoveTo::CloneInverse()
{
	return new ActionQuartMoveTo(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuartMoveTo::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionQuartMoveTo::Tween()
{
	float alpha = 0.0f;
	Vector3 vPos (0.0f ,0.0f, 0.0f);

	switch(m_eType)
	{
	case MOVE__EASEIN:
		alpha = m_fCurrTime / m_fTime;
		alpha =alpha * alpha *alpha *alpha;
		vPos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return vPos;
	case  MOVE__EASEOUT:
		alpha = m_fCurrTime / m_fTime - 1.0f;
		alpha = alpha * alpha * alpha * alpha - 1.0f;
		vPos = -(m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return vPos;
	case  MOVE__EASEINOUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f);
		if( alpha < 1.0f)
		{
			alpha = alpha * alpha * alpha * alpha;
			vPos = (m_vPosEnd - m_vPosStart) /2.0 *alpha + m_vPosStart;
		}
		else
		{
			alpha -=2.0f;
			alpha = alpha * alpha * alpha * alpha - 2.0f;
			vPos = -(m_vPosEnd - m_vPosStart) / 2.0f * alpha  + m_vPosStart;
		}
		return vPos;
	default:
		return vPos;
	}
}