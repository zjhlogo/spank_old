/*!
 * \file IRenderableObject.h
 * \date 30-07-2011 16:06:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRENDERABLEOBJECT_H__
#define __IRENDERABLEOBJECT_H__

#include "IObject.h"

class IRenderableObject : public IObject
{
public:
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

};
#endif // __IRENDERABLEOBJECT_H__
