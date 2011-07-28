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
	m_pParentNode = NULL;
	m_vPosition = IMath::VEC3_ZERO;
	m_qRotation = IMath::ROT_ZERO;
	m_vScale = IMath::VEC3_ONE;
	m_matLocal.MakeIdentity();
	m_matFinal.MakeIdentity();
}

Node_Impl::~Node_Impl()
{
	FreeChildNodes();
	ClearAttachedObjects();
}

INode* Node_Impl::CreateChildNode()
{
	Node_Impl* pNode = new Node_Impl();
	pNode->m_pParentNode = this;
	m_vChildNodes.push_back(pNode);
	return pNode;
}

bool Node_Impl::RemoveChildNode(INode* pNode)
{
	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		if (pNode == (*it))
		{
			m_vChildNodes.erase(it);
			SAFE_DELETE(pNode);
			return true;
		}
	}

	return false;
}

INode* Node_Impl::GetChildNode(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_vChildNodes.size()) return NULL;
	return m_vChildNodes[nIndex];
}

int Node_Impl::GetNumChildNodes()
{
	return (int)m_vChildNodes.size();
}

INode* Node_Impl::GetParentNode()
{
	return m_pParentNode;
}

bool Node_Impl::AttachObject(IObject* pObject)
{
	// TODO: check pObject exist?
	m_vAttachedObjects.push_back(pObject);
	return true;
}

bool Node_Impl::DettachObject(IObject* pObject)
{
	for (TV_OBJECT::iterator it = m_vAttachedObjects.begin(); it != m_vAttachedObjects.end(); ++it)
	{
		if (pObject == (*it))
		{
			m_vAttachedObjects.erase(it);
			return true;
		}
	}

	return false;
}

IObject* Node_Impl::GetAttachedObject(int nIndex)
{
	if (nIndex < 0 || nIndex >= (int)m_vAttachedObjects.size()) return NULL;
	return m_vAttachedObjects[nIndex];
}

int Node_Impl::GetNumAttachedObjects()
{
	return (int)m_vAttachedObjects.size();
}

void Node_Impl::SetPosition(const Vector3& vPos)
{
	m_vPosition = vPos;
}

const Vector3& Node_Impl::GetPosition()
{
	return m_vPosition;
}

void Node_Impl::SetRotation(const Quaternion& qRot)
{
	m_qRotation = qRot;
}

const Quaternion& Node_Impl::GetRotation()
{
	return m_qRotation;
}

void Node_Impl::SetScale(const Vector3& vScale)
{
	m_vScale = vScale;
}

const Vector3& Node_Impl::GetScale()
{
	return m_vScale;
}

const Matrix4x4& Node_Impl::GetLocalMatrix()
{
	return m_matLocal;
}

const Matrix4x4& Node_Impl::GetFinalMatrix()
{
	return m_matFinal;
}

void Node_Impl::UpdateMatrix()
{
	// TODO: setup local matrix
	// TODO: setup final matrix
	// TODO: tell children setup their matrix
}

void Node_Impl::FreeChildNodes()
{
	for (TV_NODE::iterator it = m_vChildNodes.begin(); it != m_vChildNodes.end(); ++it)
	{
		INode* pNode = (*it);
		SAFE_DELETE(pNode);
	}

	m_vChildNodes.clear();
}

void Node_Impl::ClearAttachedObjects()
{
	m_vAttachedObjects.clear();
}
