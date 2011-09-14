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
#include "INode.h"

class IRenderableObject : public IObject
{
public:
	DECLARE_RTTI(IRenderableObject, IObject);

	IRenderableObject();
	virtual ~IRenderableObject();

	void SetParentNode(INode* pNode);
	INode* GetParentNode() const;

	const Matrix4x4& GetFinalMatrix();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

private:
	INode* m_pParentNode;

};
#endif // __IRENDERABLEOBJECT_H__
