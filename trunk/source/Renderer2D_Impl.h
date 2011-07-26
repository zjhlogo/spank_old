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
	Renderer2D_Impl();
	virtual ~Renderer2D_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void SetTexture(ITexture* pTexture);

	virtual void BeginRender2D();
	virtual void EndRender2D();

	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts);
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis);

private:
	IShader* m_pShader;
	Matrix4x4 m_matOrtho;

};
#endif // __RENDERER2D_IMPL_H__
