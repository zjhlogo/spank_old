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
#include <string>
#include <map>

class IConfig  : public IMgr
{
public:
	typedef std::map<std::string, std::string> TM_STRING;
	typedef std::map<std::string, int> TM_INT;

public:
	static IConfig& GetInstance();

	virtual bool Initialize();
	virtual void Terminate();

	void AddString(const char* pszKey, const char* pszValue);
	const char* GetString(const char* pszKey, const char* pszDefaultValue = NULL);

	void AddInt(const char* pszKey, int nValue);
	int GetInt(const char* pszKey, int nDefaultValue = 0);

private:
	TM_STRING m_mapString;
	TM_INT m_mapInt;

};
#endif // __ICONFIG_H__
