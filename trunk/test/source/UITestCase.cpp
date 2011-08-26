/*!
 * \file UITestCase.cpp
 * \date 8-26-2011 17:39:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UITestCase.h"
#include <ui/UITextView.h>

UITestCase::UITestCase()
:TestCase("UITestCase")
{
	// TODO: 
}

UITestCase::~UITestCase()
{
	// TODO: 
}

bool UITestCase::Initialize(UIScreen* pUIScreen)
{
	UITextView* pTextView = new UITextView(pUIScreen, "0123456789 | /*-+. | ABCDEFG | abcedfg");
	pTextView->SetPosition(Vector2(100.0f, 100.0f));

	return true;
}

void UITestCase::Terminate()
{
	// TODO: 
}
