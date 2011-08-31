/*!
 * \file IRendererUI.h
 * \date 8-23-2011 16:02:44
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERERUI_H__
#define __IRENDERERUI_H__

#include "../IMgr.h"
#include "../ITexture.h"
#include "../BaseTypeEx.h"
#include "../math/IMath.h"

class IRendererUI : public IMgr
{
public:
	static IRendererUI& GetInstance();

	virtual void SetTexture(ITexture* pTexture) = 0;

	virtual void DrawLineList(const VATTR_POS_RGB* pVerts, uint nVerts, const ushort* pIndis, uint nIndis) = 0;
	virtual void DrawLineRect(const QUAD_VERT_POS_RGB& quad) = 0;
	virtual void DrawLineRect(const Vector2& pos, const Vector2& size) = 0;
	virtual void DrawLineRect(float x, float y, float width, float height) = 0;
	virtual void SetColor(float r, float g, float b, float a) = 0;

	virtual void DrawTriangleList(const VATTR_POS_UV* pVerts, uint nVerts, const ushort* pIndis, uint nIndis) = 0;
	virtual void DrawTriangleRect(const QUAD_VERT_POS_UV& quad) = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

};
#endif // __IRENDERERUI_H__