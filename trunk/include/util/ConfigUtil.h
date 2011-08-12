/*!
 * \file ConfigUtil.h
 * \date 10-08-2011 22:09:08
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CONFIGUTIL_H__
#define __CONFIGUTIL_H__

#include "../IMgr.h"
#include <string>
#include <map>

class ConfigUtil : public IMgr
{
public:
	typedef std::map<std::string, std::string> TM_STRING;
	typedef std::map<std::string, int> TM_INT;

public:
	ConfigUtil();
	virtual ~ConfigUtil();

	static ConfigUtil& GetInstance();

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
#endif // __CONFIGUTIL_H__
