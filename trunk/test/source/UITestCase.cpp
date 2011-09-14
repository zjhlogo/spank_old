/*!
 * \file UITestCase.cpp
 * \date 8-26-2011 17:39:27
 * 
 * 
 * \author zjhlogo (zjhlogo@gmail.com)
 */
#include "UITestCase.h"
#include <ui/UITextView.h>
#include <ui/UIButton.h>
#include <ui/UICheckButton.h>
#include <ui/UIRadioButton.h>
#include <ui/UISliderBar.h>

#include <msg/MsgID.h>
#include <util/IDebugUtil.h>

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

	/*Test show a normal button*/
	UIButton* m_pButton = new UIButton(pUIScreen);
	m_pButton->SetPosition(Vector2(10.0f, 10.0f));
	m_pButton->ConnectEvent(MI_UI_CLICKED, this,CAST_MSG_CALLBACK(&UITestCase::UITestFun));

	/* Test, show a list of Check button. you can set a callback funtion for the each CheckButton */
	for (int i = 0; i < 3; ++i)
	{
		UICheckButton* pUICheck = new UICheckButton(pUIScreen);
		pUICheck->SetPosition(Vector2(10.0f, 100.0f+i*50.0f));
	}

 	/*Test, show a list Radio button, you should get a RadioGroup first*/
	for (int i = 0; i < 3; ++i)
	{
		UIRadioButton* pUIRadio = new UIRadioButton(pUIScreen);
		pUIRadio->SetPosition(Vector2(210.0f, 100.0f+i*50.0f));
	}

 	/*Test, show a Slider, you should set a maskTexture.at last*/
 	UISliderBar* pSilder = new UISliderBar(pUIScreen);
 	pSilder->SetPosition(Vector2(10.0f, 250.0f));

	return true;
}

void UITestCase::Terminate()
{
	// TODO: 
}

void UITestCase::UITestFun(IMsgBase* pMsg)
{
// 	MsgClick* msgclick = (MsgClick*)pMsg;
// 
// 	LOGD("%d Button click Noraml or Check%d", msgclick->GetButtonID(),msgclick->ISNormal());
}
