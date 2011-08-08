/*!
 * \file ILevel2D.h
 * \date 08-08-2011 21:51:32
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ILEVEL2D_H__
#define __ILEVEL2D_H__

#include "IRenderableObject.h"
#include "math/Vector2.h"

class ILevel2D : public IRenderableObject
{
public:
	virtual void SetCenterPosition(const Vector2& pos) = 0;
	virtual const Vector2& GetCenterPosition() const = 0;

};
#endif // __ILEVEL2D_H__
