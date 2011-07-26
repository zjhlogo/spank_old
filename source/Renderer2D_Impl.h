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
#include <IShader.h>

class Renderer2D_Impl : public IRenderer2D
{
public:
	typedef struct VERTEX_ATTRIBUTE_tag
	{
		float x, y, z;
		float u, v;
	} VERTEX_ATTRIBUTE;

public:
	Renderer2D_Impl();
	virtual ~Renderer2D_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual const Matrix4x4& GetProjectionMatrix() const;
	virtual void SetMatrix(const Matrix4x4* pMat);
	virtual void SetTexture(ITexture* pTexture);

	virtual void BeginRender2D();
	virtual void EndRender2D();

	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis);
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis);
	virtual void DrawRect(float x, float y, float width, float height);

private:
	IShader* m_pShader;
	Matrix4x4 m_matOrtho;

};
#endif // __RENDERER2D_IMPL_H__
