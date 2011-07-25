/*!
 * \file VertexAttribute_Impl.h
 * \date 25-07-2011 21:18:23
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __VERTEXATTRIBUTE_IMPL_H__
#define __VERTEXATTRIBUTE_IMPL_H__

#include <IVertexAttribute.h>

class VertexAttribute_Impl : public IVertexAttribute
{
public:
	enum CONST_DEFINE
	{
		MAX_VERTEX_ATTRIBUTE = 8,
	};

public:
	VertexAttribute_Impl(const ATTRIBUTE_ITEM* pAttrItems);
	virtual ~VertexAttribute_Impl();

	virtual uint GetStride() const;
	virtual int GetNumAttributeItems() const;
	virtual const ATTRIBUTE_ITEM* GetAttributeItem(int nIndex) const;
	virtual bool operator==(const IVertexAttribute& VertexAttribute) const;

private:
	bool CreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);
	uint GetAttributeItemSize(uint nSize, ATTRIBUTE_TYPE eType);

private:
	int m_nNumItems;
	ATTRIBUTE_ITEM m_AttributeItems[MAX_VERTEX_ATTRIBUTE+1];

};
#endif // __VERTEXATTRIBUTE_IMPL_H__