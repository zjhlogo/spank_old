/*!
 * \file Config_Impl.h
 * \date 7-25-2011 10:08:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __CONFIG_IMPL_H__
#define __CONFIG_IMPL_H__

#include <IConfig.h>
#include <string>
#include <map>

class Config_Impl : public IConfig
{
public:
	typedef std::map<std::string, std::string> TM_STRING;
	typedef std::map<std::string, int> TM_INT;

public:
	virtual bool Initialize();
	virtual void Terminate();

	virtual void AddString(const char* pszKey, const char* pszValue);
	virtual const char* GetString(const char* pszKey, const char* pszDefaultValue = NULL);

	virtual void AddInt(const char* pszKey, int nValue);
	virtual int GetInt(const char* pszKey, int nDefaultValue = 0);

private:
	TM_STRING m_mapString;
	TM_INT m_mapInt;

};
#endif // __CONFIG_IMPL_H__
