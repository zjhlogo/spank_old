/*!
 * \file IRtti.h
 * \date 9-14-2011 9:02:26
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IRTTI_H__
#define __IRTTI_H__

#include "BaseType.h"

class IRtti
{
public:
	IRtti(const char* pszTypeName, const IRtti* pBaseRtti);
	~IRtti();

	const char* GetTypeName() const;
	const IRtti* GetBaseRtti() const;

	bool IsType(const char* pszTypeName) const;
	bool IsDerived(const char* pszTypeName) const;

private:
	const char* m_pszTypeName;
	const IRtti* m_pBaseRtti;

};

class INoRtti
{
public:
	INoRtti() {};
	~INoRtti() {};

	static const IRtti* __RttiData() {return NULL;};

};

#define DECLARE_RTTI(name, basename)											\
static const IRtti* __RttiData()												\
{																				\
	static const IRtti s_Rtti(#name, basename::__RttiData());					\
	return &s_Rtti;																\
};																				\
virtual const IRtti* GetRtti()													\
{																				\
	return __RttiData();														\
}																				\

#endif // __IRTTI_H__
