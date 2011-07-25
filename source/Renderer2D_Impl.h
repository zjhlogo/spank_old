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

	virtual void SetShader(IShader* pShader);

	virtual void DrawTriangleList(const void* pVerts, uint nNumVerts);
	virtual void DrawTriangleStrip(const void* pVerts, uint nNumVerts, const ushort* pIndis, uint nNumIndis);

private:
	IShader* m_pShader;

};
#endif // __RENDERER2D_IMPL_H__
