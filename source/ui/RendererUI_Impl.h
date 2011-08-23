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

class RendererUI_Impl : public IRendererUI
{
public:
	RendererUI_Impl();
	virtual ~RendererUI_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual void SetTexture(ITexture* pTexture);
	virtual void DrawRect(float x, float y, float width, float height);

	virtual void BeginRender();
	virtual void EndRender();

};
#endif // __RENDERERUI_IMPL_H__
