/*!
 * \file IRtti.cpp
 * \date 9-14-2011 9:07:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IRtti.h>

IRtti::IRtti(const char* pszTypeName, const IRtti* pParentRtti)
{
	m_pszTypeName = pszTypeName;
	m_pParentRtti = pParentRtti;
}

IRtti::~IRtti()
{
	// TODO: 
}

const char* IRtti::GetTypeName() const
{
	return m_pszTypeName;
}

const IRtti* IRtti::GetParentRtti() const
{
	return m_pParentRtti;
}

bool IRtti::IsType(const IRtti* pRtti) const
{
	return (this == pRtti);
}

bool IRtti::IsDerived(const IRtti* pRtti) const
{
	if (IsType(pRtti)) return true;

	const IRtti* pCurrRtti = m_pParentRtti;

	while (pCurrRtti)
	{
		if (pCurrRtti == pRtti) return true;
		pCurrRtti = pCurrRtti->GetParentRtti();
	}

	return false;
}
