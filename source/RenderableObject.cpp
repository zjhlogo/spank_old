/*!
 * \file RenderableObject.cpp
 * \date 14-08-2011 10:44:56
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <RenderableObject.h>

RenderableObject::RenderableObject()
{
	m_pParentNode = NULL;
}

RenderableObject::~RenderableObject()
{
	// TODO: 
}

void RenderableObject::SetParentNode(INode* pNode)
{
	m_pParentNode = pNode;
}

INode* RenderableObject::GetParentNode() const
{
	return m_pParentNode;
}

const Matrix4x4& RenderableObject::GetFinalMatrix()
{
	if (!m_pParentNode) return IMath::MAT4X4_IDENTITY;
	return m_pParentNode->GetFinalMatrix();
}
