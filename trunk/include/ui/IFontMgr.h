/*!
 * \file IFontMgr.h
 * \date 8-22-2011 15:31:09
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __IFONTMGR_H__
#define __IFONTMGR_H__

#include "IFont.h"
#include "../IMgr.h"

class IFontMgr : public IMgr
{
public:
	static IFontMgr& GetInstance();

	virtual IFont* CreateFont(const char* pszFontFile) = 0;

};
#endif // __IFONTMGR_H__
