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

class VertexAttribute : public IObject
{
public:
	enum CONST_DEFINE
	{
		MAX_NAME_LENGTH = 32,
		MAX_ATTRIBUTES = 16,
		MAX_VERTEX_ATTRIBUTE = 8,
	};

	enum ATTRIBUTE_TYPE
	{
		AT_UNKNOWN = 0,
		AT_BYTE,
		AT_UNSIGNED_BYTE,
		AT_SHORT,
		AT_UNSIGNED_SHORT,
		AT_FLOAT,
		AT_FIXED,
		AT_HALF_FLOAT_OES,
		NUM_AT,
	};

	typedef struct ATTRIBUTE_ITEM_tag
	{
		uint nSize;
		ATTRIBUTE_TYPE eItemType;
		uint nOffset;
		char szParamName[MAX_NAME_LENGTH];
	} ATTRIBUTE_ITEM;

public:
	VertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);
	virtual ~VertexAttribute();

	virtual uint GetStride() const;
	virtual int GetNumAttributeItems() const;
	virtual const ATTRIBUTE_ITEM* GetAttributeItem(int nIndex) const;
	virtual bool operator==(const VertexAttribute& VertexAttribute) const;

private:
	bool CreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems);
	uint GetAttributeItemSize(uint nSize, ATTRIBUTE_TYPE eType);

private:
	int m_nNumItems;
	ATTRIBUTE_ITEM m_AttributeItems[MAX_VERTEX_ATTRIBUTE+1];

};
#endif // __VERTEXATTRIBUTE_H__
