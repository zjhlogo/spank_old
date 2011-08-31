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
	static const char* s_pszText = "This program will allow you to generate\n"
								   "bitmap fonts from TrueType fonts.\n\n"
								   "The application generates both image\n"
								   "files and character descriptions that\n"
								   "can be read by a game for easy\n"
								   "rendering of fonts.";

	UITextView* pTextView = new UITextView(pUIScreen, s_pszText);
	pTextView->SetPosition(Vector2(80.0f, 50.0f));

	return true;
}

void UITestCase::Terminate()
{
	// TODO: 
}
