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
#include <ui/UISilder.h>
#include <ITextureMgr.h>
#include <msg/MsgID.h>
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

	UIButton* m_pButton = new UIButton(pUIScreen);
	m_pButton->SetPosition(Vector2(0.0f, 50.0f));
	m_pButton->SetNormalTexture(ITextureMgr::GetInstance().CreateTexture("ButtonNormal.png"));
	m_pButton->SetPressedTexture(ITextureMgr::GetInstance().CreateTexture("ButtonPressed.png"));
	
	UISilder* pSilder = new UISilder(pUIScreen);

	pSilder->SetPosition(Vector2(50,100));
	pSilder->SetMaskBarTexture(ITextureMgr::GetInstance().CreateTexture("f_buyin_009.png"));
	pSilder->SetNormalBarTexture(ITextureMgr::GetInstance().CreateTexture("f_buyin_010.png"));
	pSilder->SetArrowTexture(ITextureMgr::GetInstance().CreateTexture("f_buyin_006.png"));
	return true;
}

void UITestCase::Terminate()
{
	// TODO: 
}
