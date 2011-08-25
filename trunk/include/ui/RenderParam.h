/*!
 * \file RenderParam.h
 * \date 8-25-2011 15:53:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERPARAM_H__
#define __RENDERPARAM_H__

#include "../math/IMath.h"

class RenderParam
{
public:
	RenderParam(const Vector2& pos, const Vector2& size);
	RenderParam(const RenderParam& param);
	~RenderParam();

	RenderParam& operator=(const RenderParam& param);

public:
	Vector2 m_vBasePos;
	Vector2 m_vBaseSize;

};
#endif // __RENDERPARAM_H__
