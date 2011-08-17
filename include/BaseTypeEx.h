/*!
 * \file BaseTypeEx.h
 * \date 14-08-2011 11:03:03
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __BASETYPEEX_H__
#define __BASETYPEEX_H__

#include "BaseType.h"

typedef struct VATTR_POS_UV_tag
{
	float x, y, z;
	float u, v;
} VATTR_POS_UV;

enum ATTRIBUTE_ITEM_TYPE
{
	AIT_UNKNOWN = 0,
	AIT_BYTE,
	AIT_UNSIGNED_BYTE,
	AIT_SHORT,
	AIT_UNSIGNED_SHORT,
	AIT_FLOAT,
	AIT_FIXED,
	AIT_HALF_FLOAT_OES,
	NUM_AIT,
};

#define MAX_ATTRIBUTE_NAME_LENGTH (32)
#define MAX_ATTRIBUTE_ITEMS (8)

typedef struct ATTRIBUTE_ITEM_tag
{
	uint nSize;
	ATTRIBUTE_ITEM_TYPE eItemType;
	uint nOffset;
	char szParamName[MAX_ATTRIBUTE_NAME_LENGTH];
} ATTRIBUTE_ITEM;

enum SYSTEM_SHADER_IDS
{
	SSI_DEFAULT = 1,
};

enum ACTION_UPDATE_TYPE
{
	AUT_UNKNOWN = 0,

	AUT_SCALE,
	AUT_POSITION,
	AUT_ROTATION,

	AUT_START,
	AUT_PAUSE,
	AUT_STOPED,

	AUT_SUBACTION_START,
	AUT_SUBACTION_PAUSE,
	AUT_SUBACTION_STOPED,
};

#endif // __BASETYPEEX_H__
