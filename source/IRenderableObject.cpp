/*!
 * \file IRenderableObject.cpp
 * \date 14-08-2011 10:44:56
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IRenderableObject.h>

IRenderableObject::IRenderableObject()
{
	m_pParentNode = NULL;
}

IRenderableObject::~IRenderableObject()
{
	// TODO: 
}

void IRenderableObject::SetParentNode(INode* pNode)
{
	m_pParentNode = pNode;
}

INode* IRenderableObject::GetParentNode() const
{
	return m_pParentNode;
}

const Matrix4x4& IRenderableObject::GetFinalMatrix()
{
	if (!m_pParentNode) return IMath::MAT4X4_IDENTITY;
	return m_pParentNode->GetFinalMatrix();
}
