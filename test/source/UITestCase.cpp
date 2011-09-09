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
#include <ui/UISlider.h>
#include <ui/UIRadioGroup.h>
#include <ui/UICheck.h>
#include <ITextureMgr.h>
#include <msg/MsgID.h>
#include <util/IDebugUtil.h>
#include "GameApp.h"
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
	m_pButton->SetPosition(Vector2(0.0f, 0.0));
	m_pButton->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png", TST_LINEAR));
	m_pButton->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png",TST_LINEAR));
	m_pButton->ConnectEvent(MI_UI_CLICKED, this,CAST_MSG_CALLBACK(&UITestCase::UITestFun));
	/*Test, show a Slider, you should set a maskTexture.at last*/
	UISlider* pSilder = new UISlider(pUIScreen);
	pSilder->SetPosition(Vector2(200,20.0f));
	pSilder->SetMaskBarTexture(ITextureMgr::GetInstance().CreateTexture("f_buyin_009.png", TST_LINEAR));
	pSilder->SetNormalBarTexture(ITextureMgr::GetInstance().CreateTexture("f_buyin_010.png", TST_LINEAR));	
	pSilder->SetArrowTexture(ITextureMgr::GetInstance().CreateTexture("f_buyin_006.png", TST_LINEAR));
	
	/* Test, show a list of Check button. you can set a callback funtion for the each CheckButton */
	UICheck* pUICheck1 = new UICheck(pUIScreen);
	pUICheck1->SetPosition(Vector2( 0.0f, 150.0f));
	pUICheck1->SetID(4);
	pUICheck1->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png",TST_LINEAR));
	pUICheck1->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png", TST_LINEAR));
	pUICheck1->ConnectEvent(MI_UI_CLICKED, this,CAST_MSG_CALLBACK(&UITestCase::UITestFun));

	UICheck* pUICheck2 = new UICheck(pUIScreen);
	pUICheck2->SetPosition(Vector2(0,200));
	pUICheck2->SetID(5);
	pUICheck2->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png",TST_LINEAR));
	pUICheck2->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png",TST_LINEAR));
	pUICheck2->ConnectEvent(MI_UI_CLICKED, this,CAST_MSG_CALLBACK(&UITestCase::UITestFun));

	UICheck* pUICheck3 = new UICheck(pUIScreen);
	pUICheck3->SetPosition(Vector2(0,100));
	pUICheck3->SetID(6);
	pUICheck3->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png",TST_LINEAR));
	pUICheck3->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png",TST_LINEAR));
	pUICheck3->ConnectEvent(MI_UI_CLICKED, this,CAST_MSG_CALLBACK(&UITestCase::UITestFun));

	/*Test, show a list Radio button, you should get a RadioGroup first*/
	UIRadioGroup* uiRadioGroup = new UIRadioGroup(pUIScreen);
	uiRadioGroup->SetPosition(Vector2(0.0f, 300.0f));
	uiRadioGroup->SetSize (Vector2(100.0f , 600.0f));
	uiRadioGroup->ConnectEvent(MI_UI_CLICKED, this,CAST_MSG_CALLBACK(&UITestCase::UITestFun));

	UIRadio* pUIRadio1 = new UIRadio(uiRadioGroup);
	pUIRadio1->SetPosition(Vector2( 0.0f, 0.0));
	pUIRadio1->SetID(1);
	pUIRadio1->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png",TST_LINEAR));
	pUIRadio1->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png", TST_LINEAR));

	UIRadio* pUIRadio2 = new UIRadio(uiRadioGroup);
	pUIRadio2->SetPosition(Vector2( 0.0f, 50.0));
	pUIRadio2->SetID(2);
	pUIRadio2->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png",TST_LINEAR));
	pUIRadio2->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png", TST_LINEAR));

	UIRadio* pUIRadio3 = new UIRadio(uiRadioGroup);
	pUIRadio3->SetPosition(Vector2( 0.0f, 100.0));
	pUIRadio3->SetID(3);
	pUIRadio3->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png",TST_LINEAR));
	pUIRadio3->SetCheckedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png", TST_LINEAR));
	return true;
}

void UITestCase::Terminate()
{
	// TODO: 
}

void UITestCase::UITestFun( IMsgBase* pMsg )
{
	MsgClick* msgclick = (MsgClick*)pMsg;

	LOGD("%d Button click Noraml or Check%d", msgclick->GetButtonID(),msgclick->ISNormal());
}
