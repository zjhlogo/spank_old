/*!
 * \file ISprite.h
 * \date 30-07-2011 16:06:05
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ISPRITE_H__
#define __ISPRITE_H__

#include "IRenderableObject.h"

class ISprite : public IRenderableObject
{
public:
	static ISprite* CreateSprite(const char* pszSpriteFile);

	virtual void SetLoop(bool bLoop) = 0;

};
#endif // __ISPRITE_H__
