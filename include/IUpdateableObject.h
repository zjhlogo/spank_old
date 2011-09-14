/*!
 * \file IUpdateableObject.h
 * \date 9-14-2011 13:28:50
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IUPDATEABLEOBJECT_H__
#define __IUPDATEABLEOBJECT_H__

#include "IObject.h"

class IUpdateableObject : public IObject
{
public:
	DECLARE_RTTI(IUpdateableObject, IObject);
	virtual void Update(float dt) = 0;

};
#endif // __IUPDATEABLEOBJECT_H__
