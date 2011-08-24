/*!
 * \file FontMgr_Impl.h
 * \date 8-22-2011 15:33:13
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __FONTMGR_IMPL_H__
#define __FONTMGR_IMPL_H__

#include <ui/IFontMgr.h>
#include <msg/IMsgBase.h>
#include <map>
#include <string>

class FontMgr_Impl : public IFontMgr
{
public:
	typedef std::map<std::string, IFont*> TM_FONT;

public:
	FontMgr_Impl();
	virtual ~FontMgr_Impl();

	virtual bool Initialize();
	virtual void Terminate();

	virtual IFont* CreateFont(const char* pszFontFile);
	virtual IFont* GetDefaultFont();

private:
	IFont* FindFont(const char* pszFontFile);
	bool OnFontDestroied(IMsgBase* pMsg);

private:
	TM_FONT m_mapFont;
	IFont* m_pDefaultFont;

};
#endif // __FONTMGR_IMPL_H__
