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
#include "math/IMath.h"

class IRenderer2D : public IMgr
{
public:
	static IRenderer2D& GetInstance();

	virtual const Matrix4x4& GetProjectionMatrix() const = 0;
	virtual void SetMatrix(const Matrix4x4* pMat) = 0;
	virtual void SetTexture(ITexture* pTexture) = 0;

	virtual void BeginRender2D() = 0;
	virtual void EndRender2D() = 0;

	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis) = 0;
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis) = 0;

	virtual void DrawRect(float x, float y, float width, float height) = 0;

	/*!
	 * \brief below shows the points order
	 * 
	 *     v1---------v3
	 *     |  \       |
	 *     |     \    |
	 *     |        \ |
	 *     v0---------v2
	 *
	 * two triangles: t1(v0, v1, v2) and t1(v1, v3, v2)
	 *
	 * \param pVerts
	 * \return 
	 */
	virtual void DrawRect(const void* pVerts) = 0;

};
#endif // __IRENDERER2D_H__
