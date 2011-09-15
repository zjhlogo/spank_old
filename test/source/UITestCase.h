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
	DECLARE_RTTI(UITestCase, TestCase);

	UITestCase();
	virtual ~UITestCase();

	virtual bool Initialize(UIScreen* pUIScreen);
	virtual void Terminate();

private:
	void OnButtonClicked(IMsgBase* pMsg);
	void OnCheckButtonChecked(IMsgBase* pMsg);
	void OnRadioButtonChecked(IMsgBase* pMsg);
	void OnSlider(IMsgBase* pMsg);

};
#endif // __UITESTCASE_H__
