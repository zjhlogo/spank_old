/*!
 * \file TweentActionMove.h
 * \date 2011/09/16 14:34
 *	
 *	
 * \author:	wbaoqing(wbaoqin@gmail.com)
 */
#ifndef __TWEENACTIONMOVE_H_
#define __TWEENACTIONMOVE_H_

#include "TestCase.h"
#include <Sprite.h>


class TweenActionMove :public TestCase
{
public:
	DECLARE_RTTI(TweenActionMove, TestCase);

	TweenActionMove();
	virtual ~TweenActionMove();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();
private:
	Sprite* m_pSpriteAction;
	INode* m_pActionNode;
};


#endif//__TWEENACTIONMOVE_H_