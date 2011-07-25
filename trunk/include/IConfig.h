/*!
 * \file IConfig.h
 * \date 23-07-2011 08:07:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ICONFIG_H__
#define __ICONFIG_H__

#include "IMgr.h"

class IConfig  : public IMgr
{
public:
	static IConfig& GetInstance();

	virtual void AddString(const char* pszKey, const char* pszValue) = 0;
	virtual const char* GetString(const char* pszKey, const char* pszDefaultValue = NULL) = 0;

	virtual void AddInt(const char* pszKey, int nValue) = 0;
	virtual int GetInt(const char* pszKey, int nDefaultValue = 0) = 0;

};
#endif // __ICONFIG_H__
