/*!
 * \file Node_Impl.h
 * \date 7-28-2011 17:46:40
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __NODE_IMPL_H__
#define __NODE_IMPL_H__

#include <INode.h>

class Node_Impl : public INode
{
public:
	Node_Impl();
	virtual ~Node_Impl();

	virtual INode* CreateChildNode();
	virtual bool RemoveChildNode(INode* pNode);
	virtual INode* GetChildNode(int nIndex);
	virtual int GetNumChildNodes();

	virtual bool AttachObject(IObject* pObject);
	virtual bool DettachObject(IObject* pObject);
	virtual IObject* GetAttachedObject(int nIndex);
	virtual int GetNumAttachedObjects();

	virtual void SetPosition(const Vector3& vPos);
	virtual const Vector3& GetPosition();

	virtual void SetRotation(const Quaternion& qRot);
	virtual const Quaternion& GetRotation();

	virtual const Matrix4x4& GetLocalMatrix();
	virtual const Matrix4x4& GetFinalMatrix();

};
#endif // __NODE_IMPL_H__
