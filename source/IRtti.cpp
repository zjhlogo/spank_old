/*!
 * \file IRtti.cpp
 * \date 9-14-2011 9:07:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IRtti.h>

IRtti::IRtti(const char* pszTypeName, const IRtti* pBaseRtti)
{
	m_pszTypeName = pszTypeName;
	m_pBaseRtti = pBaseRtti;
}

IRtti::~IRtti()
{
	// TODO: 
}

const char* IRtti::GetTypeName() const
{
	return m_pszTypeName;
}

const IRtti* IRtti::GetBaseRtti() const
{
	return m_pBaseRtti;
}

bool IRtti::IsType(const char* pszTypeName) const
{
	return m_pszTypeName == pszTypeName;
}

bool IRtti::IsDerived(const char* pszTypeName) const
{
	const IRtti* pRtti = m_pBaseRtti;

	while (pRtti)
	{
		if (pRtti->GetTypeName() == pszTypeName) return true;
		pRtti = pRtti->GetBaseRtti();
	}

	return false;
}
