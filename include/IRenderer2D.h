/*!
 * \file IRenderer2D.h
 * \date 7-25-2011 10:31:46
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERER2D_H__
#define __IRENDERER2D_H__

#include "IMgr.h"
#include "IShader.h"

class IRenderer2D : public IMgr
{
public:
	static IRenderer2D& GetInstance();

	virtual void SetTexture(ITexture* pTexture) = 0;

	virtual void BeginRender2D() = 0;
	virtual void EndRender2D() = 0;

	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts) = 0;
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis) = 0;

};
#endif // __IRENDERER2D_H__
