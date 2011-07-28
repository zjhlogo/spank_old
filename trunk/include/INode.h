/*!
 * \file INode.h
 * \date 7-28-2011 17:26:37
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __INODE_H__
#define __INODE_H__

#include "math/IMath.h"
#include "IObject.h"

class INode : public IObject
{
public:
	virtual INode* CreateChildNode() = 0;
	virtual bool RemoveChildNode(INode* pNode) = 0;
	virtual INode* GetChildNode(int nIndex) = 0;
	virtual int GetNumChildNodes() = 0;

	virtual bool AttachObject(IObject* pObject) = 0;
	virtual bool DettachObject(IObject* pObject) = 0;
	virtual IObject* GetAttachedObject(int nIndex) = 0;
	virtual int GetNumAttachedObjects() = 0;

	virtual void SetPosition(const Vector3& vPos) = 0;
	virtual const Vector3& GetPosition() = 0;

	virtual void SetRotation(const Quaternion& qRot) = 0;
	virtual const Quaternion& GetRotation() = 0;

	virtual const Matrix4x4& GetLocalMatrix() = 0;
	virtual const Matrix4x4& GetFinalMatrix() = 0;
};

#endif // __INODE_H__
