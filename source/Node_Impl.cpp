/*!
 * \file Node_Impl.cpp
 * \date 7-28-2011 17:46:47
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Node_Impl.h"

Node_Impl::Node_Impl()
{
	// TODO: 
}

Node_Impl::~Node_Impl()
{
	// TODO: 
}

INode* Node_Impl::CreateChildNode()
{
	// TODO: 
	return NULL;
}

bool Node_Impl::RemoveChildNode(INode* pNode)
{
	// TODO: 
	return false;
}

INode* Node_Impl::GetChildNode(int nIndex)
{
	// TODO: 
	return NULL;
}

int Node_Impl::GetNumChildNodes()
{
	// TODO: 
	return 0;
}

bool Node_Impl::AttachObject(IObject* pObject)
{
	// TODO: 
	return false;
}

bool Node_Impl::DettachObject(IObject* pObject)
{
	// TODO: 
	return false;
}

IObject* Node_Impl::GetAttachedObject(int nIndex)
{
	// TODO: 
	return NULL;
}

int Node_Impl::GetNumAttachedObjects()
{
	// TODO: 
	return 0;
}

void Node_Impl::SetPosition(const Vector3& vPos)
{
	// TODO: 
}

const Vector3& Node_Impl::GetPosition()
{
	// TODO: 
	return IMath::VEC3_ZERO;
}

void Node_Impl::SetRotation(const Quaternion& qRot)
{
	// TODO: 
}

const Quaternion& Node_Impl::GetRotation()
{
	// TODO: 
	return IMath::ROT_ZERO;
}

const Matrix4x4& Node_Impl::GetLocalMatrix()
{
	// TODO: 
	return IMath::MAT4X4_IDENTITY;
}

const Matrix4x4& Node_Impl::GetFinalMatrix()
{
	// TODO: 
	return IMath::MAT4X4_IDENTITY;
}
