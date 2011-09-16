/*!
 * \file ClipRectTestCase.cpp
 * \date 2011/09/15 15:22
 *	
 *	
 * \author:	wbaoqing(wbaoqing@gmail.com)
 */
#include "ClipRectTestCase.h"
#include "ClipTest.h"
ClipRectTestCase::ClipRectTestCase()
:TestCase("ClipRectTestCase")
{
	//TODO:
}

ClipRectTestCase::~ClipRectTestCase()
{
	//TODO:
}

bool ClipRectTestCase::Initialize( UIScreen* pUIScreen )
{
	//TODO:
	ClipTest* pClipTest;
	
	//左上
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(100.0f, 50.0f));
	pClipTest->SetClip(100.0f, 50.0f, 40.0f, 15.0f);
	//左下
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(100.0f, 100.0));
	pClipTest->SetClip(100.0f,115.0,40.0f,15.0);

	//右上
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(200.0f, 50.0f));
	pClipTest->SetClip(240.0f,50.0,50.0,15.0);

	//右下
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(200.0f, 100.0f));
	pClipTest->SetClip(240.0, 115.0f, 50.0f, 15.0f);

	//左半

	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(100.0f, 150.0f));
	pClipTest->SetClip(100.0f, 150.0f, 50.0f, 40.0);
	//右半
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(200.0f, 150.0f));
	pClipTest->SetClip(240.0, 150.0f, 50.0f, 40.0f);

	//上半
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(100.0f, 200.0));
	pClipTest->SetClip(100.0f, 200.0f, 100.0f, 15.0f);

	//下半
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(200.0f, 200.0f));
	pClipTest->SetClip(200.0f, 215.0f, 100.0f, 15.0f);
	
	//全部
	pClipTest = new ClipTest(pUIScreen);
	pClipTest->SetPosition(Vector2(100.0f, 250.0f));
	pClipTest->SetClip(100.0f, 250.0f, 100.0f, 60.0f);
	return true;

}

void ClipRectTestCase::Terminate()
{
	//TODO:
}


void ClipRectTestCase::OnButtonClicked( IMsgBase* pMsg )
{
	//TODO:
}

void ClipRectTestCase::OnCheckButtonChecked( IMsgBase* pMsg )
{
	//TODO:
}

void ClipRectTestCase::OnRadioButtonChecked( IMsgBase* pMsg )
{
	//TODO:
}

void ClipRectTestCase::OnSlider( IMsgBase* pMsg )
{
	//TODO:
}
