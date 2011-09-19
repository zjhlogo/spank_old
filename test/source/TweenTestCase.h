/*!
 * \file TweenTestCase.h
 * \date 2011/09/16 14:34
 *	
 *	
 * \author:	wbaoqing(wbaoqin@gmail.com)
 */
#ifndef __TWEENTESTCASE_H__
#define __TWEENTESTCASE_H__

#include "TestCase.h"
#include <Sprite.h>

class TweenTestCase : public TestCase
{
public:
	DECLARE_RTTI(TweenTestCase, TestCase);

	TweenTestCase();
	virtual ~TweenTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();
	virtual void Render();
private:
	void OnPrvButton(IMsgBase* pMsg);
	void OnNextButton(IMsgBase* pMsg);

	void ConnectAction(uint nIndex);

private:
	Sprite* m_pSpriteAction;
	INode* m_pActionNode;
	uint m_nIndexTween;
	uint m_nEffectIndex;
};
#endif // __TWEENTESTCASE_H__
