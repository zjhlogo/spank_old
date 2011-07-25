/*!
 * \file IConfig.cpp
 * \date 23-07-2011 08:11:00
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include <IConfig.h>

IConfig& IConfig::GetInstance()
{
	static IConfig s_IConfig;
	return s_IConfig;
}

bool IConfig::Initialize()
{
	return true;
}

void IConfig::Terminate()
{
	m_mapString.clear();
	m_mapInt.clear();
}

void IConfig::AddString(const char* pszKey, const char* pszValue)
{
	std::string strKey = pszKey;
	std::string strValue = pszValue;
	m_mapString.insert(std::make_pair(strKey, strValue));
}

const char* IConfig::GetString(const char* pszKey, const char* pszDefaultValue /*= NULL*/)
{
	std::string strKey = pszKey;
	TM_STRING::iterator itfound = m_mapString.find(strKey);
	if (itfound == m_mapString.end()) return pszDefaultValue;

	return itfound->second.c_str();
}

void IConfig::AddInt(const char* pszKey, int nValue)
{
	std::string strKey = pszKey;
	m_mapInt.insert(std::make_pair(strKey, nValue));
}

int IConfig::GetInt(const char* pszKey, int nDefaultValue /* = 0 */)
{
	std::string strKey = pszKey;
	TM_INT::iterator itfound = m_mapInt.find(strKey);
	if (itfound == m_mapInt.end()) return nDefaultValue;

	return itfound->second;
}
