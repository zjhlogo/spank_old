/*!
 * \file RenderParam.cpp
 * \date 8-25-2011 15:53:51
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <ui/RenderParam.h>

RenderParam::RenderParam(const Vector2& pos, const Vector2& size)
{
	m_vBasePos = pos;
	m_vBaseSize = size;
}

RenderParam::RenderParam(const RenderParam& param)
{
	m_vBasePos = param.m_vBasePos;
	m_vBaseSize = param.m_vBaseSize;
}

RenderParam::~RenderParam()
{
	// TODO: 
}

RenderParam& RenderParam::operator=(const RenderParam& param)
{
	m_vBasePos = param.m_vBasePos;
	m_vBaseSize = param.m_vBaseSize;
	return (*this);
}
