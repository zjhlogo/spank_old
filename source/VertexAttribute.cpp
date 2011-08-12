/*!
 * \file VertexAttribute.cpp
 * \date 25-07-2011 21:20:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <VertexAttribute.h>
#include <memory.h>
#include <string.h>

VertexAttribute::VertexAttribute(const ATTRIBUTE_ITEM* pAttrItems)
{
	m_nNumItems = 0;
	memset(m_AttributeItems, 0, sizeof(m_AttributeItems));
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

const VertexAttribute::ATTRIBUTE_ITEM* VertexAttribute::GetAttributeItem(int nIndex) const
{
	if (nIndex < 0 || nIndex >= m_nNumItems) return NULL;
	return &m_AttributeItems[nIndex];
}

bool VertexAttribute::operator==(const VertexAttribute& VertexAttribute) const
{
	if (m_nNumItems != VertexAttribute.GetNumAttributeItems()) return false;

	for (int i = 0; i < m_nNumItems; ++i)
	{
		const VertexAttribute::ATTRIBUTE_ITEM* pAttrItem = VertexAttribute.GetAttributeItem(i);

		if (m_AttributeItems[i].nSize != pAttrItem->nSize) return false;
		if (m_AttributeItems[i].eItemType != pAttrItem->eItemType) return false;
		if (strcmp(m_AttributeItems[i].szParamName, pAttrItem->szParamName) != 0) return false;
	}

	return true;
}

bool VertexAttribute::CreateVertexAttribute(const ATTRIBUTE_ITEM* pAttrItems)
{
	int nNumItems = 0;
	const ATTRIBUTE_ITEM* pCurrItem = pAttrItems;
	while (pCurrItem && pCurrItem->eItemType != AT_UNKNOWN)
	{
		nNumItems++;
		pCurrItem++;
	}

	if (nNumItems <= 0 || nNumItems > MAX_VERTEX_ATTRIBUTE) return false;

	m_nNumItems = nNumItems;
	uint nOffset = 0;
	for (int i = 0; i < nNumItems; ++i)
	{
		m_AttributeItems[i].nSize = pAttrItems[i].nSize;
		m_AttributeItems[i].eItemType = pAttrItems[i].eItemType;
		m_AttributeItems[i].nOffset = nOffset;
		strncpy(m_AttributeItems[i].szParamName, pAttrItems[i].szParamName, MAX_NAME_LENGTH);
		m_AttributeItems[i].szParamName[MAX_NAME_LENGTH-1] = '\0';
		nOffset += GetAttributeItemSize(m_AttributeItems[i].nSize, m_AttributeItems[i].eItemType);
	}
	m_AttributeItems[m_nNumItems].nSize = 0;
	m_AttributeItems[m_nNumItems].eItemType = AT_UNKNOWN;
	m_AttributeItems[m_nNumItems].nOffset = nOffset;
	m_AttributeItems[m_nNumItems].szParamName[0] = '\0';

	return true;
}

uint VertexAttribute::GetAttributeItemSize(uint nSize, ATTRIBUTE_TYPE eType)
{
	static const int s_ItemSizes[NUM_AT] =
	{
		0, // AT_UNKNOWN,
		1, // AT_BYTE,
		1, // AT_UNSIGNED_BYTE,
		2, // AT_SHORT,
		2, // AT_UNSIGNED_SHORT,
		4, // AT_FLOAT,
		4, // AT_FIXED,
		2, // AT_HALF_FLOAT_OES,
	};

	if (eType <= AT_UNKNOWN || eType >= NUM_AT) return 0;
	return nSize*s_ItemSizes[eType];
}
