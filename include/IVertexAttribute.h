/*!
 * \file IVertexAttribute.h
 * \date 25-07-2011 21:06:25
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IVERTEXATTRIBUTE_H__
#define __IVERTEXATTRIBUTE_H__

#include "IObject.h"

class IVertexAttribute : public IObject
{
public:
	enum CONST_DEFINE
	{
		MAX_NAME_LENGTH = 32,
	};

	enum ATTRIBUTE_TYPE
	{
		AT_UNKNOWN,
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
	virtual uint GetStride() const = 0;
	virtual int GetNumAttributeItems() const = 0;
	virtual const ATTRIBUTE_ITEM* GetAttributeItem(int nIndex) const = 0;
	virtual bool operator ==(const IVertexAttribute& VertexAttribute) const = 0;

};
#endif // __IVERTEXATTRIBUTE_H__
