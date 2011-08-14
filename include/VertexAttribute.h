/*!
 * \file VertexAttribute.h
 * \date 25-07-2011 21:18:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __VERTEXATTRIBUTE_H__
#define __VERTEXATTRIBUTE_H__

#include "IObject.h"
#include "BaseTypeEx.h"

class VertexAttribute : public IObject
{
public:
	VertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);
	virtual ~VertexAttribute();

	virtual uint GetStride() const;
	virtual int GetNumAttributeItems() const;
	virtual const ATTRIBUTE_ITEM* GetAttributeItem(int nIndex) const;
	virtual bool operator==(const VertexAttribute& VertexAttribute) const;

private:
	bool CreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);
	uint GetAttributeItemSize(uint nSize, ATTRIBUTE_ITEM_TYPE eType);

private:
	int m_nNumItems;
	ATTRIBUTE_ITEM m_AttributeItems[MAX_ATTRIBUTE_ITEMS+1];

};
#endif // __VERTEXATTRIBUTE_H__
