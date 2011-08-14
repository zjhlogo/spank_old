/*!
 * \file RenderableObject.h
 * \date 30-07-2011 16:06:57
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __RENDERABLEOBJECT_H__
#define __RENDERABLEOBJECT_H__

#include "IObject.h"
#include "INode.h"

class RenderableObject : public IObject
{
public:
	RenderableObject();
	virtual ~RenderableObject();

	void SetParentNode(INode* pNode);
	INode* GetParentNode() const;

	const Matrix4x4& GetFinalMatrix();

	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

private:
	INode* m_pParentNode;

};
#endif // __RENDERABLEOBJECT_H__
