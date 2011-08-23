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

class IRendererUI : public IMgr
{
public:
	static IRendererUI& GetInstance();

	virtual void SetTexture(ITexture* pTexture) = 0;
	virtual void DrawRect(float x, float y, float width, float height) = 0;

	virtual void BeginRender() = 0;
	virtual void EndRender() = 0;

};
#endif // __IRENDERERUI_H__
