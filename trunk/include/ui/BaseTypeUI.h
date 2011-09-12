/*!
 * \file BaseTypeUI.h
 * \date 8-25-2011 13:21:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BASETYPEUI_H__
#define __BASETYPEUI_H__

#include "../BaseTypeEx.h"

enum UI_TOUCH_EVENT_TYPE
{
	UTET_UNKNOWN,
	UTET_BEGIN,
	UTET_MOVE,
	UTET_END,
};

typedef struct CHAR_INFO_tag
{
	int nID;
	float width, height;
	float u, v, du, dv;
	ITexture* pTexture;
	float offsetx, offsety, advance;
	int nRef;
} CHAR_INFO;

#endif // __BASETYPEUI_H__
