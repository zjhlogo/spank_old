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
#include "action/IActionBase.h"

class RenderableObject;
class INode : public IObject
{
public:
	virtual INode* CreateChildNode() = 0;
	virtual bool RemoveChildNode(INode* pNode) = 0;
	virtual INode* GetChildNode(int nIndex) = 0;
	virtual int GetNumChildNodes() = 0;
	virtual INode* GetParentNode() = 0;

	virtual bool AttachObject(RenderableObject* pObject) = 0;
	virtual bool DettachObject(RenderableObject* pObject) = 0;
	virtual RenderableObject* GetAttachedObject(int nIndex) = 0;
	virtual int GetNumAttachedObjects() = 0;

	virtual void SetPosition(const Vector3& vPos) = 0;
	virtual void SetPosition(float x, float y, float z) = 0;
	virtual const Vector3& GetPosition() = 0;

	virtual void SetRotation(const Quaternion& qRot) = 0;
	virtual void SetRotation(const Vector3& vNormal, float fRadian) = 0;
	virtual const Quaternion& GetRotation() = 0;

	virtual void SetScale(const Vector3& vScale) = 0;
	virtual void SetScale(float x, float y, float z) = 0;
	virtual const Vector3& GetScale() = 0;

	virtual void RunAction(IActionBase* pAction) = 0;

	virtual const Matrix4x4& GetLocalMatrix() = 0;
	virtual const Matrix4x4& GetFinalMatrix() = 0;

	virtual void UpdateMatrix(float dt) = 0;
	virtual void UpdateAction(float dt) = 0;
	virtual void UpdateObjects(float dt) = 0;
	virtual void RenderObjects() = 0;

};

#endif // __INODE_H__
