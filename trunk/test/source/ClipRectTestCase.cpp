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

	for (int i = 0; i < 10; i++)
	{
		pClipTest = new ClipTest(pUIScreen);
		pClipTest->SetPosition(Vector2(100.0f,i*50.0f));
		pClipTest->SetClip(100.0f, i*50.0f, 10.0f * i, 20.0f * i);
	}
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
