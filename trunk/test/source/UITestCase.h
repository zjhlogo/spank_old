/*!
 * \file UITestCase.h
 * \date 8-26-2011 17:39:22
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#ifndef __UITESTCASE_H__
#define __UITESTCASE_H__

#include "TestCase.h"

class UITestCase : public TestCase
{
public:
	UITestCase();
	virtual ~UITestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();
	
	void UITestFun(IMsgBase* pMsg);
};
#endif // __UITESTCASE_H__
