/*!
 * \file RendererUI_Impl.h
 * \date 8-23-2011 17:32:55
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERERUI_IMPL_H__
#define __RENDERERUI_IMPL_H__

#include <ui/IRendererUI.h>
#include "VertexCache.h"
#include <IShader.h>

class RendererUI_Impl : public IRendererUI
{
public:
	enum CONST_DEFINE
	{
		VERTS_PER_QUAD = 4,
		INDIS_PER_QUAD = 6,

		NUM_CACHES = 5,
		NUM_QUAD_PER_CACHE = 128,
		VERTEX_ATTRIBUTE_SIZE = 20,
		VERTS_CACHE_SIZE = NUM_QUAD_PER_CACHE*VERTS_PER_QUAD*VERTEX_ATTRIBUTE_SIZE,
		INDIS_CACHE_SIZE = NUM_QUAD_PER_CACHE*INDIS_PER_QUAD,
	};

public:
	RendererUI_Impl();
	virtual ~RendererUI_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void SetTexture(ITexture* pTexture);
	virtual void DrawTriangleList(const void* pVerts, uint nVerts, const ushort* pIndis, uint nIndis);
	virtual void DrawRect(const void* pVerts);
	virtual void DrawRect(float x, float y, float width, float height);

	virtual void BeginRender();
	virtual void EndRender();

private:
	VertexCache* m_pVertexCaches[NUM_CACHES];

	ITexture* m_pTexture;
	IShader* m_pShader;

	bool m_bRenderBegan;

};
#endif // __RENDERERUI_IMPL_H__
