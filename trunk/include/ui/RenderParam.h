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
#include "../BaseType.h"

class RenderParam
{
public:
	enum RENDER_STATE
	{
		RS_ENABLE = 0x00000001,
		RS_DEFAULT = RS_ENABLE,

		RS_FORCE_32BIT = 0x7FFFFFFF,
	};

public:
	RenderParam(const Vector2& pos, const Vector2& size);
	RenderParam(const RenderParam& param);
	~RenderParam();

	RenderParam& operator=(const RenderParam& param);

	void SetRenderState(uint nMask, bool bEnable);
	bool CheckRenderState(uint nMask);

public:
	Vector2 m_vBasePos;
	Vector2 m_vBaseSize;
	uint m_nRenderState;

};
#endif // __RENDERPARAM_H__
