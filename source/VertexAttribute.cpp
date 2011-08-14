/*!
 * \file VertexAttribute.cpp
 * \date 25-07-2011 21:20:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <VertexAttribute.h>
#include <memory.h>
#include <util/StringUtil.h>

VertexAttribute::VertexAttribute(const ATTRIBUTE_ITEM* pAttrItems)
{
	m_nNumItems = 0;
	StringUtil::ZeroMemory(m_AttributeItems, sizeof(m_AttributeItems));
	m_bOK = CreateVertexAttribute(pAttrItems);
}

VertexAttribute::~VertexAttribute()
{
	// TODO: 
}

uint VertexAttribute::GetStride() const
{
	return m_AttributeItems[m_nNumItems].nOffset;
}

int VertexAttribute::GetNumAttributeItems() const
{
	return m_nNumItems;
}

const ATTRIBUTE_ITEM* VertexAttribute::GetAttributeItem(int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nNumItems) return NULL;
	return &m_AttributeItems[nIndex];
}

bool VertexAttribute::operator==(const VertexAttribute& VertexAttribute) const
{
	if (m_nNumItems != VertexAttribute.GetNumAttributeItems()) return false;

	for (int i = 0; i < m_nNumItems; ++i)
	{
		const ATTRIBUTE_ITEM* pAttrItem = VertexAttribute.GetAttributeItem(i);

		if (m_AttributeItems[i].nSize != pAttrItem->nSize) return false;
		if (m_AttributeItems[i].eItemType != pAttrItem->eItemType) return false;
		if (!StringUtil::IsEqual(m_AttributeItems[i].szParamName, pAttrItem->szParamName)) return false;
	}

	return true;
}

bool VertexAttribute::CreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems)
{
	int nNumItems = 0;
	const ATTRIBUTE_ITEM* pCurrItem = pAttrItems;
	while (pCurrItem && pCurrItem->eItemType != AIT_UNKNOWN)
	{
		nNumItems++;
		pCurrItem++;
	}

	if (nNumItems <= 0 || nNumItems > MAX_ATTRIBUTE_ITEMS) return false;

	m_nNumItems = nNumItems;
	uint nOffset = 0;
	for (int i = 0; i < nNumItems; ++i)
	{
		m_AttributeItems[i].nSize = pAttrItems[i].nSize;
		m_AttributeItems[i].eItemType = pAttrItems[i].eItemType;
		m_AttributeItems[i].nOffset = nOffset;
		StringUtil::CopyString(m_AttributeItems[i].szParamName, MAX_ATTRIBUTE_NAME_LENGTH, pAttrItems[i].szParamName);
		nOffset += GetAttributeItemSize(m_AttributeItems[i].nSize, m_AttributeItems[i].eItemType);
	}
	m_AttributeItems[m_nNumItems].nSize = 0;
	m_AttributeItems[m_nNumItems].eItemType = AIT_UNKNOWN;
	m_AttributeItems[m_nNumItems].nOffset = nOffset;
	m_AttributeItems[m_nNumItems].szParamName[0] = '\0';

	return true;
}

uint VertexAttribute::GetAttributeItemSize(uint nSize, ATTRIBUTE_ITEM_TYPE eType)
{
	static const int s_ItemSizes[NUM_AIT] =
	{
		0, // AIT_UNKNOWN,
		1, // AIT_BYTE,
		1, // AIT_UNSIGNED_BYTE,
		2, // AIT_SHORT,
		2, // AIT_UNSIGNED_SHORT,
		4, // AIT_FLOAT,
		4, // AIT_FIXED,
		2, // AIT_HALF_FLOAT_OES,
	};

	if (eType <= AIT_UNKNOWN || eType >= NUM_AIT) return 0;
	return nSize*s_ItemSizes[eType];
}
