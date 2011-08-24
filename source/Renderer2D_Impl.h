/*!
 * \file Renderer2D_Impl.h
 * \date 7-25-2011 10:43:33
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERER2D_IMPL_H__
#define __RENDERER2D_IMPL_H__

#include <IRenderer2D.h>

class Renderer2D_Impl : public IRenderer2D
{
public:
	Renderer2D_Impl();
	virtual ~Renderer2D_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void SetModelViewMatrix(const Matrix4x4& mat);
	virtual const Matrix4x4& GetModelViewMatrix() const;

	virtual void SetProjectionMatrix(const Matrix4x4& mat);
	virtual const Matrix4x4& GetProjectionMatrix() const;

	virtual const Matrix4x4& GetFinalMatrix();
	virtual const Matrix4x4& GetFinalMatrixTranspose();

	virtual void BeginRender();
	virtual void EndRender();

	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader);
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis, IShader* pShader);

	virtual void DrawRect(float x, float y, float width, float height, IShader* pShader);
	virtual void DrawRect(const QUAD_VERT_POS_UV& quadVerts, IShader* pShader);

private:
	void UpdateFinalMatrix();

private:
	Matrix4x4 m_matModelView;
	Matrix4x4 m_matProj;
	Matrix4x4 m_matModelViewProj;
	Matrix4x4 m_matModelViewProjTranspose;
	bool m_bNeedUpdateFinalMatrix;

};
#endif // __RENDERER2D_IMPL_H__
