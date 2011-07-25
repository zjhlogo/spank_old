/*!
 * \file Config_Impl.cpp
 * \date 7-25-2011 10:11:11
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "Config_Impl.h"

IConfig& IConfig::GetInstance()
{
	static Config_Impl s_Config_Impl;
	return s_Config_Impl;
}

bool Config_Impl::Initialize()
{
	return true;
}

void Config_Impl::Terminate()
{
	m_mapString.clear();
	m_mapInt.clear();
}

void Config_Impl::AddString(const char* pszKey, const char* pszValue)
{
	std::string strKey = pszKey;
	std::string strValue = pszValue;
	m_mapString.insert(std::make_pair(strKey, strValue));
}

const char* Config_Impl::GetString(const char* pszKey, const char* pszDefaultValue /*= NULL*/)
{
	std::string strKey = pszKey;
	TM_STRING::iterator itfound = m_mapString.find(strKey);
	if (itfound == m_mapString.end()) return pszDefaultValue;

	return itfound->second.c_str();
}

void Config_Impl::AddInt(const char* pszKey, int nValue)
{
	std::string strKey = pszKey;
	m_mapInt.insert(std::make_pair(strKey, nValue));
}

int Config_Impl::GetInt(const char* pszKey, int nDefaultValue /* = 0 */)
{
	std::string strKey = pszKey;
	TM_INT::iterator itfound = m_mapInt.find(strKey);
	if (itfound == m_mapInt.end()) return nDefaultValue;

	return itfound->second;
}
