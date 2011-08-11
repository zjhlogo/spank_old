/*!
 * \file ScreenUtil.cpp
 * \date 8-11-2011 11:27:48
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <util/ScreenUtil.h>
#include <util/ConfigUtil.h>

ScreenUtil::ScreenUtil()
{
	m_nScreenWidth = 0;
	m_nScreenHeight = 0;
	m_eScreenRotation = SR_NONE;
}

ScreenUtil::~ScreenUtil()
{
	// TODO: 
}

ScreenUtil& ScreenUtil::GetInstance()
{
	static ScreenUtil s_ScreenUtil;
	return s_ScreenUtil;
}

bool ScreenUtil::Initialize()
{
	m_eScreenRotation = (SCREEN_ROTATION)ConfigUtil::GetInstance().GetInt("SCREEN_ROTATION", SR_NONE);
	switch (m_eScreenRotation)
	{
	case SR_P90:
	case SR_N90:
		m_nScreenWidth = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
		m_nScreenHeight = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
		break;
	default:
		m_nScreenWidth = ConfigUtil::GetInstance().GetInt("SURFACE_WIDTH");
		m_nScreenHeight = ConfigUtil::GetInstance().GetInt("SURFACE_HEIGHT");
		break;
	}

	return true;
}

void ScreenUtil::Terminate()
{
	// TODO: 
}

int ScreenUtil::GetScreenWidth() const
{
	return m_nScreenWidth;
}

int ScreenUtil::GetScreenHeight() const
{
	return m_nScreenHeight;
}

ScreenUtil::SCREEN_ROTATION ScreenUtil::GetScreenRotation() const
{
	return m_eScreenRotation;
}

float ScreenUtil::GetRotationDegree() const
{
	static float s_Degree[NUM_SR] =
	{
		  0.0f,
		-90.0f,
		 90.0f,
		180.0f,
	};

	return s_Degree[m_eScreenRotation];
}

void ScreenUtil::PointToScreen(Vector2& vPosOut, float x, float y)
{
	switch (m_eScreenRotation)
	{
	case SR_P90:
		{
			vPosOut.x = y;
			vPosOut.y = m_nScreenHeight - x;
		}
		break;
	case SR_N90:
		{
			vPosOut.x = m_nScreenWidth - y;
			vPosOut.y = x;
		}
		break;
	case SR_180:
		{
			vPosOut.x = m_nScreenWidth - x;
			vPosOut.y = m_nScreenHeight - y;
		}
		break;
	default:
		{
			vPosOut.x = x;
			vPosOut.y = y;
		}
		break;
	}
}

void ScreenUtil::PointToScreen(Vector2& vPosOut, const Vector2& pos)
{
	PointToScreen(vPosOut, pos.x, pos.y);
}

void ScreenUtil::PointToScreen(Vector2& vPosInOut)
{
	PointToScreen(vPosInOut, vPosInOut.x, vPosInOut.y);
}
