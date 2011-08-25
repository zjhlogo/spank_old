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

class IRendererUI : public IMgr
{
public:
	static IRendererUI& GetInstance();

	virtual void SetTexture(ITexture* pTexture) = 0;
	virtual void DrawTriangleList(const void* pVerts, uint nVerts, const ushort* pIndis, uint nIndis) = 0;
	virtual void DrawRect(const QUAD_VERT_POS_UV& quadVerts) = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

};
#endif // __IRENDERERUI_H__
