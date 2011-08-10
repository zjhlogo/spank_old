/*!
 * \file Input_Impl.cpp
 * \date 8-09-2011 17:52:21
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Input_Impl.h"
#include <IDebugUtil.h>

IInput& IInput::GetInstance()
{
	static Input_Impl s_Input_Impl;
	return s_Input_Impl;
}

Input_Impl::Input_Impl()
{
	memset(m_TouchInfoCache, 0, sizeof(m_TouchInfoCache));
	m_nAllocIndex = 0;
}

Input_Impl::~Input_Impl()
{
	// TODO: 
}

bool Input_Impl::Initialize()
{
	memset(m_TouchInfoCache, 0, sizeof(m_TouchInfoCache));
	m_nAllocIndex = 0;
	while (!m_TouchInfoQueue.empty()) m_TouchInfoQueue.pop();
	return true;
}

void Input_Impl::Terminate()
{
	// TODO: 
}

void Input_Impl::OnTouchStart(int nIndex, float x, float y)
{
	TOUCH_INFO* pInfo = AllocTouchInfo();
	if (!pInfo)
	{
		LOGE("touch queue full");
		return;
	}

	pInfo->eType = TT_START;
	pInfo->x = x;
	pInfo->y = y;
	m_TouchInfoQueue.push(pInfo);
}

void Input_Impl::OnTouch(int nIndex, float x, float y)
{
	TOUCH_INFO* pInfo = AllocTouchInfo();
	if (!pInfo)
	{
		LOGE("touch queue full");
		return;
	}

	pInfo->eType = TT_MOVE;
	pInfo->x = x;
	pInfo->y = y;
	m_TouchInfoQueue.push(pInfo);
}

void Input_Impl::OnTouchEnd(int nIndex, float x, float y)
{
	TOUCH_INFO* pInfo = AllocTouchInfo();
	if (!pInfo)
	{
		LOGE("touch queue full");
		return;
	}

	pInfo->eType = TT_END;
	pInfo->x = x;
	pInfo->y = y;
	m_TouchInfoQueue.push(pInfo);
}

void Input_Impl::DispatchTouchEvents()
{
	while (!m_TouchInfoQueue.empty())
	{
		TOUCH_INFO* pInfo = m_TouchInfoQueue.front();
		m_TouchInfoQueue.pop();

		// TODO: send message to notify input event

		FreeTouchInfo(pInfo);
	}
}

Input_Impl::TOUCH_INFO* Input_Impl::AllocTouchInfo()
{
	for (int i = 0; i < TOUCH_INFO_CACHE_SIZE; ++i)
	{
		if (m_TouchInfoCache[m_nAllocIndex].eType == TT_UNKNOWN)
		{
			int nIndex = m_nAllocIndex;
			m_nAllocIndex = ((++m_nAllocIndex) % TOUCH_INFO_CACHE_SIZE);
			m_TouchInfoCache[nIndex].eType = TT_ALLOCATED;
			return &m_TouchInfoCache[nIndex];
		}

		m_nAllocIndex = ((++m_nAllocIndex) % TOUCH_INFO_CACHE_SIZE);
	}

	return NULL;
}

void Input_Impl::FreeTouchInfo(TOUCH_INFO* pInfo)
{
	pInfo->eType = TT_UNKNOWN;
}
