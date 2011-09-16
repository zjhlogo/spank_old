/*!
 * \file ActionQuadraticMove.cpp
 * \date 2011/09/16 11:27
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include <action/ActionQuadMove.h>

ActionQuadMove::ActionQuadMove(uint eType, const Vector3& posStart, const Vector3& posEnd, float time )
{
	m_vPosStart = posStart;
	m_vPosEnd = posEnd;
	m_fTime = time;
	m_eType = eType;
	Reset();
}

void ActionQuadMove::Reset()
{
	m_fCurrTime = 0.0f;
}

void ActionQuadMove::Update( float dt )
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

IActionBase* ActionQuadMove::Clone()
{
	return new ActionQuadMove(m_eType, m_vPosStart, m_vPosEnd, m_fTime);
}

IActionBase* ActionQuadMove::CloneInverse()
{
	return new ActionQuadMove(m_eType, m_vPosEnd, m_vPosStart, m_fTime);
}

float ActionQuadMove::GetTimeLength() const
{
	return m_fTime;
}

Vector3 ActionQuadMove::Tween()
{
	Vector3 pos(0.0f, 0.0f, 0.0f);
	float alpha = 0.0f;

	switch (m_eType)
	{
	case MOVE__EASEIN:
		alpha = m_fCurrTime / m_fTime;
		alpha *= alpha;
		pos = (m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return pos;
	case MOVE__EASEOUT:
		alpha = m_fCurrTime / m_fTime;
		alpha = alpha * (alpha - 2.0f);
		pos = -(m_vPosEnd - m_vPosStart) * alpha + m_vPosStart;
		return pos;
	case MOVE__EASEINOUT:
		alpha = m_fCurrTime / (m_fTime / 2.0f) ;
		if(alpha < 1.0f)
		{
			alpha = alpha *alpha;
			pos = (m_vPosEnd - m_vPosStart) / 2.0f * alpha + m_vPosStart;
		}
		else
		{	alpha = ((alpha - 1.0f) * (alpha - 3.0f) - 1.0f);
			pos =  - ((m_vPosEnd - m_vPosStart) / 2.0f )* alpha + m_vPosStart;
		}
		return pos;
	default:
		return pos;
	}
}
