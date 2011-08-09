/*!
 * \file ICore.h
 * \date 23-07-2011 11:14:17
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __ICORE_H__
#define __ICORE_H__

#include "IMgr.h"
#include "INode.h"

class ICore : public IMgr
{
public:
	enum CONST_DEFINE
	{
		MAX_TOUCHES_SUPPORT = 4,
	};

	enum TOUCH_TYPE
	{
		TT_UNKNOWN = 0,
		TT_BEGIN,
		TT_MOVE,
		TT_END,
	};

	typedef struct TOUCH_INFO_tag
	{
		TOUCH_TYPE eType;
		float x, y;
	} TOUCH_INFO;

public:
	static ICore& GetInstance();

	virtual INode* GetRootNode() = 0;

	virtual void Update(float dt) = 0;

	virtual void PreRender() = 0;
	virtual void Render() = 0;
	virtual void PostRender() = 0;

	virtual void OnTouchEvent(int nIndex, TOUCH_TYPE eType, float x, float y) = 0;

};
#endif // __ICORE_H__
