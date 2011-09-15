/*!
 * \file ClipRectTestCase.h
 * \date 2011/09/15 15:22
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */

#ifndef __CLIPRECTESTCASE_H_
#define __CLIPRECTESTCASE_H_

#include "TestCase.h"


class ClipRectTestCase :public TestCase
{
public:
	DECLARE_RTTI(ClipRectTestCase, TestCase);

	ClipRectTestCase();
	virtual ~ClipRectTestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

private:
	void OnButtonClicked(IMsgBase* pMsg);
	void OnCheckButtonChecked(IMsgBase* pMsg);
	void OnRadioButtonChecked(IMsgBase* pMsg);
	void OnSlider(IMsgBase* pMsg);
};
#endif//__CLIPRECTESTCASE_H_