/*!
 * \file IRenderer.h
 * \date 7-20-2011 17:37:38
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERER_H__
#define __IRENDERER_H__

#include "BaseType.h"

class IRenderer
{
public:
	static IRenderer& GetInstance();

	virtual bool Initialize(int width, int height) = 0;
	virtual void Terminate() = 0;
	virtual void RenderTest() = 0;

};

#endif // __IRENDERER_H__
